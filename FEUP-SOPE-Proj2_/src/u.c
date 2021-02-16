#include "../include/common_utils.h" // Here for testing
#include "../include/u_parseArgs.h"
#include "../include/requests.h"
#include "../include/handle_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h> 
#include <sys/types.h>
#include <sys/times.h> 
#include <unistd.h> 
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>

int thread_interval = MILI_MICRO(10);   /**interval between threads creation in miliseconds*/
int max_duration = 15;     /**Max miliseconds a user can be at the bathroom*/

static bool isBathroomClosed = false;
static char fifoname[MAX_FIFONAME];

static inline int generateTime(){       //return in microseconds
    return rand()%max_duration+1; 
}

static inline void getFifoPath(pid_t pid, pthread_t tid, char * path){
    sprintf(path, "/tmp/%d.%lu", pid, tid);  
}

void * user(void * pos){
    Request request;
    request.i = *(int *) pos;
    request.pid = getpid();
    request.tid = pthread_self();
    request.dur = generateTime();
    request.pl = -1;
    
    free((int*) pos);
    char path[MAX_FIFONAME]; 
    getFifoPath(request.pid, request.tid, path);

    char *requestSemName = (char *) malloc((strlen(fifoname + 5) + 5) * sizeof(char));
    strncpy(requestSemName, fifoname + 5, strlen(fifoname + 5));
    strcat(requestSemName, ".sem");
    
    sem_t *requestSem = sem_open(requestSemName, 0);
    if (requestSem == SEM_FAILED) {
        request.dur = -1;
        request.pl = -1;
        log_entry(&request, "FAILD");
        isBathroomClosed = true;
        free(requestSemName);
        sem_close(requestSem);
        pthread_exit(NULL);
    }
    free(requestSemName);

    int fd_public;
    fd_public = open(fifoname, O_WRONLY);
    if (fd_public == -1) {
        perror("Failed to open private FIFO");
        pthread_exit(NULL);
    }

    // We create FIFO here to garantee that the sv can make the open() call
    // without failing instantly due to the FIFO not being created yet
    if (mkfifo(path, 0660) < 0) {
        fprintf(stderr, "%s:%d error on creating fifo called %s", __FILE__, __LINE__, path); 
        close(fd_public);
        pthread_exit(NULL);
    }

    int write_ret = write(fd_public, &request, sizeof(Request));
    if (write_ret <= 0)
    {
        if (errno == EPIPE) {
            log_entry(&request, "FAILD");
            isBathroomClosed = true;
        }
        else
            perror("Failed to write to public FIFO"); 

        close(fd_public);
        unlink(path);
        pthread_exit(NULL); 
    }

    sem_post(requestSem); // Here to let the sv know it has a client
    sem_close(requestSem);

    log_entry(&request, "IWANT");

    int fd_private;
    fd_private = open(path, O_RDONLY);
    if (fd_private == -1) {
        perror("Failed to open private FIFO");
        close(fd_public);
        unlink(path);
        pthread_exit(NULL);
    }

    close(fd_public);
    // TL:DR: This one here garantees that the server has read the request
    // Otherwise, the server's read would return 0 because all pipe write ends
    // had been closed, aka "oh shit of fuck". The sv would skip a read, and the
    // request sem would forever be 1 request behind, which would in turn make all
    // the following requests success (except the last because delay)
    // This problem only ocurred from the 2nd iteration forward, because in the first
    // one the call to `open()` sv side was performed, so it waited and always
    // succeeded

    int read_ret = read(fd_private, &request, sizeof(Request));
    if (read_ret == -1 || (read_ret != sizeof(Request) && read_ret != 0)) {
        // God help us if this gets here
        // EBADF is impossible
        log_entry(&request, "FAILD");
        close(fd_private);
        unlink(path);
        pthread_exit(NULL);
    }

    close(fd_private);
    unlink(path);

    if (request.pl != -1)
        log_entry(&request, "IAMIN");
    else
        log_entry(&request, "CLOSD");

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    Info_u info_u; 
    int i = 0; 

    if (parseArgs(argc, argv, &info_u)){
        fprintf(stderr, "%s:%d   ./u <-t secs> fifoname\n", __FILE__, __LINE__); 
        exit(1);
    }

    memcpy(fifoname, info_u.fifoname, sizeof(info_u.fifoname));

    time_t end = time(NULL) + info_u.secs;
    while(time(NULL) < end && !isBathroomClosed){
        pthread_t thrd;
        int *request_num = (int*) malloc(sizeof(int));
        if (request_num == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            pthread_exit(NULL);
        }
        *request_num = i++;
        if (pthread_create(&thrd, NULL, user, (void*) request_num) < 0){
            fprintf(stderr, "%s:%d  not able to create thread\n", __FILE__, __LINE__);
            pthread_exit(NULL);
        }
        pthread_detach(thrd);
        usleep(thread_interval);
    }
 
    pthread_exit(NULL); 
}
