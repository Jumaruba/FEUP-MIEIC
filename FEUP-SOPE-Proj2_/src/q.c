#include "../include/q_singleton.h"

#include "../include/queue.h"
#include "../include/requests.h"
#include "../include/handle_log.h"
#include "../include/common_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <errno.h>
#include <signal.h>

#define SERVER_TIMEOUT 10

// Used for limited capacity
static Queue_t *q = NULL;
static pthread_mutex_t mutex_q = PTHREAD_MUTEX_INITIALIZER;

static sem_t threads_available;
static sem_t bathrooms_available;

static void vacate_bathroom(int bathroom_id) {
    if (get_q_args()->limited_capacity) {
        int *aux = (int*) malloc(sizeof(int));
        if (aux == NULL) {
            fprintf(stderr, "Failed to allocate an int... Expect a bathroom unused forever\n");
            return;
        }
        *aux = bathroom_id;

        pthread_mutex_lock(&mutex_q);
        if (queue_push_back(q, aux)) {
            fprintf(stderr, "Failed to push vacant bathroom back\n");
        }
        pthread_mutex_unlock(&mutex_q);

        sem_post(&threads_available);
        sem_post(&bathrooms_available);
    }
}

static void vacate_thread() {
    if (get_q_args()->limited_capacity) {
        sem_post(&threads_available);
    }
}

static void *client_handler(void *arg) {

    Request *initial_req = (Request *) arg;
    int bathroom_place = initial_req->pl;
    initial_req->pl = -1;
    log_entry(initial_req, "RECVD");

    Request request;

    request.pid = getpid();
    request.tid = pthread_self();
    request.i = initial_req->i;
    request.dur = initial_req->dur;
    request.pl = bathroom_place;

    char name[200];
    sprintf(name, "/tmp/%d.%lu", initial_req->pid, initial_req->tid);

    int private_fifo_fd;
    private_fifo_fd = open(name, O_WRONLY);
    if (private_fifo_fd == -1) {
        perror("Failed to open private FIFO");
        free(initial_req);
        vacate_bathroom(bathroom_place);
        pthread_exit(NULL);
    }

    if (write(private_fifo_fd, &request, sizeof(Request)) != sizeof(Request)) {
        if (errno == EBADF || errno == EPIPE)
            log_entry(&request, "GAVUP");
        else
            perror("Faile to write back to private FIFO");
        
        free(initial_req);
        close(private_fifo_fd);
        vacate_bathroom(bathroom_place);
        pthread_exit(NULL);
    }

    // Notified client that the bathroom was free
    log_entry(&request, "ENTER");

    if (usleep(MILI_MICRO(initial_req->dur))) {
        // Handle EINTR gracefully?
        perror("Failed to sleep correctly");
        if (errno == EINVAL) {
            perror("Duration is too large (unsupported on this system)");
            free(initial_req);
            close(private_fifo_fd);
            vacate_bathroom(bathroom_place);
            pthread_exit(NULL);
        }
    }

    log_entry(&request, "TIMUP");

    free(initial_req);
    close(private_fifo_fd);
    vacate_bathroom(bathroom_place);
    pthread_exit(NULL);
}

void *dismiss_client(void *arg) {
    Request *initial_req = (Request *) arg;
    log_entry(initial_req, "RECVD");

    Request request;

    request.pid = getpid();
    request.tid = pthread_self();
    request.i = initial_req->i;
    request.dur = -1;
    request.pl = -1;

    char name[200];
    sprintf(name, "/tmp/%d.%ld", initial_req->pid, initial_req->tid);

    int private_fifo_fd;
    private_fifo_fd = open(name, O_WRONLY);
    if (private_fifo_fd == -1) {
        perror("Failed to open private FIFO");
        free(initial_req);
        vacate_thread();
        pthread_exit(NULL);
    }

    if (write(private_fifo_fd, &request, sizeof(Request)) != sizeof(Request)) {
        if (errno == EBADF || errno == EPIPE)
            log_entry(&request, "GAVUP");
        else
            perror("Failed to write back to private FIFO");
        
        free(initial_req);
        close(private_fifo_fd);
        vacate_thread();
        pthread_exit(NULL);
    }

    // Notified client that the bathroom has closed
    log_entry(&request, "2LATE");

    free(initial_req);
    close(private_fifo_fd);
    vacate_thread();
    pthread_exit(NULL);
}

void server_cleanup() {
    char *requestSemName = (char *) malloc((strlen(get_q_args()->request_fifo + 5) + 5) * sizeof(char));
    strncpy(requestSemName, get_q_args()->request_fifo + 5, strlen(get_q_args()->request_fifo + 5));
    strcat(requestSemName, ".sem");
    sem_unlink(requestSemName);
    free(requestSemName);

    sem_close(&bathrooms_available);
    sem_close(&threads_available);

    unlink(get_q_args()->request_fifo);

    free_queue_and_data(q);
    q = NULL;
    free_q_singleton();
}

void sigint_handler() {
    exit(1);
}

void empty_alarm_handler() {
    printf("No clients were received...\n");
}

int main(int argc, char *argv[]) {

    // Used for the bathroom's number in unlimited mode
    int request_no = 0;

    if (parse_args(argc, argv)) {
        perror("Failed to parse command line arguments");
        exit(1);
    }

    atexit(server_cleanup);

    struct sigaction act;
    memset(&act, 0, sizeof(act));
    if (sigemptyset(&act.sa_mask)) {
        perror("Error on sigemptyset");
        exit(1);
    }
    act.sa_handler = sigint_handler;
    if (sigaction(SIGINT, &act, NULL) < 0) {
        perror("Error setting up SIGINT handler");
        exit(1);
    }
    act.sa_handler = empty_alarm_handler;
    if (sigaction(SIGALRM, &act, NULL) < 0) {
        perror("Error setting up SIGALRM handler");
        exit(1);
    }

    if (get_q_args()->force && access(get_q_args()->request_fifo, F_OK) == 0) {
        unlink(get_q_args()->request_fifo);
    }

    if (mkfifo(get_q_args()->request_fifo, 0660)) {
        perror("Failed to create FIFO");
        exit(1);
    }

    if (get_q_args()->limited_capacity) {
        
        q = new_queue(get_q_args()->nplaces);
        if (q == NULL) {
            fprintf(stderr, "Failed to instantiate bathroom queue\n");
            exit(1);
        }

        for (int i = 1; i < get_q_args()->nplaces + 1; ++i) {
            int *aux = malloc(sizeof(int));
            if (aux == NULL) {
                fprintf(stderr, "Failed to allocate bathroom queue members\n");
                exit(1);
            }
            *aux = i;
            if (queue_push_back(q, aux)) {
                fprintf(stderr, "Failed to push back bathroom queue member\n");
                exit(1);
            }
        }

        if (sem_init(&threads_available, 0, get_q_args()->nthreads)) {
            perror("Failed to initialize bathrooms available sempahore\n");
            exit(1);
        }

        if (sem_init(&bathrooms_available, 0, get_q_args()->nplaces)) {
            perror("Failed to initialize bathrooms available sempahore\n");
            exit(1);
        }
    }

    // [5] is here to skip the "/tmp/"
    char *requestSemName = (char *) malloc((strlen(get_q_args()->request_fifo + 5) + 5) * sizeof(char));
    strncpy(requestSemName, get_q_args()->request_fifo + 5, strlen(get_q_args()->request_fifo + 5));
    strcat(requestSemName, ".sem");
    sem_t *requestSem = sem_open(requestSemName, O_CREAT, 0660, 0);
    if (requestSem == SEM_FAILED) {
        perror("Failed to create and open request semaphore");
        free(requestSemName);
        exit(1);
    }

    time_t end_time = time(NULL) + get_q_args()->nsecs;
    struct timespec sem_timeout = getTimespecIn(get_q_args()->nsecs, 1);

    bool openedFifoFd = false;
    alarm(get_q_args()->nsecs); // This alarm is safe to use because there are no other threads
    int fifo_fd = open(get_q_args()->request_fifo, O_RDONLY);
    alarm(0);

    if (fifo_fd == -1) {
        if (errno != EINTR) {
            perror("Failed to open request FIFO");
            sem_close(requestSem);
            sem_unlink(requestSemName);
            free(requestSemName);
            unlink(get_q_args()->request_fifo);
            exit(1);
        }
    }
    else {
        openedFifoFd = true;
    }

    while (openedFifoFd && time(NULL) < end_time) {

        if (sem_timedwait(requestSem, &sem_timeout)) {
            if (errno == ETIMEDOUT) {
                // Timed out, never got a single client
                break;
            }
            else {
                perror("Failed on sem_timedwait for opening the FIFO");
                sem_close(requestSem);
                sem_unlink(requestSemName);
                free(requestSemName);
                if (openedFifoFd) {
                    close(fifo_fd);
                    unlink(get_q_args()->request_fifo);
                }
                pthread_exit(NULL);
            }
        }

        Request *read_request = (Request*) malloc(sizeof(Request));
        if (read_request == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            sem_close(requestSem);
            sem_unlink(requestSemName);
            free(requestSemName);
            close(fifo_fd);
            unlink(get_q_args()->request_fifo);
            pthread_exit(NULL);
        }

        int read_ret;
        read_ret = read(fifo_fd, read_request, sizeof(Request));
        if (read_ret == -1 || (read_ret != sizeof(Request) && read_ret != 0)) {
            // God help us if this gets here
            // EBADF is impossible
            perror("Failed to read from FIFO");
            free(read_request);
            sem_close(requestSem);
            sem_unlink(requestSemName);
            free(requestSemName);
            close(fifo_fd);
            unlink(get_q_args()->request_fifo);
            pthread_exit(NULL);
        }
        if (read_ret == 0) {
            // All write end processes closed, so we must free Request
            free(read_request);
            printf("NULL REQUEST %d\n", request_no);
        }
        else {
            // We're here, so the read was successful
            if (get_q_args()->limited_capacity && (sem_timedwait(&bathrooms_available, &sem_timeout)
                    || sem_timedwait(&threads_available, &sem_timeout))) {

                // This will never run with unlimited bathrooms
                if (errno == ETIMEDOUT) {
                    // Timed out, no more available bathrooms
                    // Dismiss current request
                    pthread_t thrd; 
                    if (pthread_create(&thrd, NULL, dismiss_client, (void *) read_request)) {
                        perror("Failed to create thread");
                        sem_close(requestSem);
                        sem_unlink(requestSemName);
                        free(read_request);
                        close(fifo_fd);
                        unlink(get_q_args()->request_fifo);
                        pthread_exit(NULL);
                    }
                    pthread_detach(thrd);
                }
                else {
                    perror("Failed on sem_timedwait for available bathrooms");
                    sem_close(requestSem);
                    sem_unlink(requestSemName);
                    free(requestSemName);
                    if (openedFifoFd) {
                        close(fifo_fd);
                        unlink(get_q_args()->request_fifo);
                    }
                    pthread_exit(NULL);
                }
            }
            else {
                // Get bathroom and dispatch
                if (get_q_args()->limited_capacity) {
                    // Limited capacity
                    pthread_mutex_lock(&mutex_q);
                    int *bathroom_number = (int*) queue_pop(q);
                    pthread_mutex_unlock(&mutex_q);
                    if (bathroom_number == NULL) {
                        sem_close(requestSem);
                        sem_unlink(requestSemName);           
                        free(read_request);
                        close(fifo_fd);
                        unlink(get_q_args()->request_fifo);
                        pthread_exit(NULL);
                    }
                    read_request->pl = *bathroom_number;
                    free(bathroom_number);
                }
                else // Unlimited capacity
                    read_request->pl = ++request_no;

                pthread_t thrd;
                if (pthread_create(&thrd, NULL, client_handler, (void *) read_request)) {
                    perror("Failed to create thread");
                    sem_close(requestSem);
                    sem_unlink(requestSemName);
                    free(read_request);
                    close(fifo_fd);
                    unlink(get_q_args()->request_fifo);
                    pthread_exit(NULL);
                }
                pthread_detach(thrd);
            }
        }
    }

    // ACCEPT NO MORE REQUESTS
    sem_close(requestSem);
    sem_unlink(requestSemName);
    free(requestSemName);

    // We timed out, so we should notify others that it's all ogre now
    if (openedFifoFd) {
        int read_ret = 1; // Enter the loop

        while (read_ret > 0) {
            Request *read_request = (Request*) malloc(sizeof(Request));
            if (read_request == NULL) {
                fprintf(stderr, "Failed to allocate memory\n");
                close(fifo_fd);
                unlink(get_q_args()->request_fifo);
                pthread_exit(NULL);
            }

            read_ret = read(fifo_fd, read_request, sizeof(Request));
            if (read_ret == -1 || (read_ret != sizeof(Request) && read_ret != 0)) {
                // God help us if this gets here
                perror("Failed to read from FIFO");
                free(read_request);
                close(fifo_fd);
                unlink(get_q_args()->request_fifo);
                pthread_exit(NULL);
            }
            else if (read_ret == 0) {
                // Free the request that won't be handled by a thread
                free(read_request);
            }
            else {
                
                if (get_q_args()->limited_capacity && sem_wait(&threads_available)) {
                    perror("Failed on sem_timedwait for available bathrooms");
                    free(read_request);
                    close(fifo_fd);
                    unlink(get_q_args()->request_fifo);
                    pthread_exit(NULL);
                }

                // We're here, so the read was successful
                pthread_t thrd;
                if (pthread_create(&thrd, NULL, dismiss_client, (void *) read_request)) {
                    perror("Failed to create thread");
                    free(read_request);
                    close(fifo_fd);
                    unlink(get_q_args()->request_fifo);
                    pthread_exit(NULL);
                }
                pthread_detach(thrd);
            }
        }
    }

    close(fifo_fd);
    unlink(get_q_args()->request_fifo);
    pthread_exit(NULL);
}
