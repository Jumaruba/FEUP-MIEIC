#include "../include/showDirec.h"
#include <sys/wait.h>
#include <unistd.h>
#include "../include/queue.h"
#include <sys/types.h>
#include <signal.h>

#define STAT_BLOCK_SIZE 512


static ssize_t read_fileInfo(FileInfo *fi, int fileno) {
    return read(fileno, fi, sizeof(*fi));
}

static ssize_t write_fileInfo(FileInfo *fi, int fileno) {
    return write(fileno, fi, sizeof(*fi));
}

// Calculate only before printing
long int calculate_size(long int size, Options *opt) {
    // Quick ceiling q = (x + y - 1) / y;
    return (size + opt->block_size - 1) / opt->block_size;
}

// For safekeeping :D
static inline long int get_size(struct stat *st, Options *opt) {
    return opt->apparent_size ?
        st->st_size
        : st->st_blocks * STAT_BLOCK_SIZE;
}

static inline void print_fileInfo(FileInfo *fi, Options *opt) {
    printf("%ld\t%s\n", calculate_size(fi->file_size, opt), fi->name);
}

static void handle_file_output(FileInfo *fi, Options *opt) {
    if (opt->all && (!opt->max_depth || opt->depth_val > 0)) {
        if (opt->original_process){
            print_fileInfo(fi, opt);
        }
        else {
            write_fileInfo(fi, STDOUT_FILENO);   
            log_info_pipe(fi, SEND_PIPE); 
        }
    }

}

// IMPORTANT: Handles only directories read from the pipe
static inline void handle_dir_output(FileInfo *fi, Options *opt) {
    // This never handles the case of printing the original
    // processe's directory at the end of everything
    if (opt->original_process) {
        if (!opt->max_depth || opt->depth_val > 0){
            print_fileInfo(fi, opt);
        }
    }
    else {
        // Only case where we want to re-send the directory
        if (!opt->max_depth || opt->depth_val > 0){
            write_fileInfo(fi, STDOUT_FILENO);
            log_info_pipe(fi, SEND_PIPE);
        }
    }
    
}

/**
 * @brief Launches all childs needed, one per subdirectory
 * 
 * @param dir_q 
 * @param pipe_q 
 * @param opt 
 */
static void launch_dirs(Queue_t *dir_q, Queue_t *pipe_q, Options *opt) {
    while (!queue_is_empty(dir_q)) {
            char *sub_dir = (char*) queue_pop(dir_q);
            
            int *new_pipe = (int*) malloc(sizeof(int[2]));
            if (new_pipe == NULL) {
                perror("Failed to allocate memory for the pipe");
                opt->return_val = 1;
                exit(1);
            }
            queue_push_back(pipe_q, new_pipe);

            if (pipe(new_pipe)) {
                perror("Failed to create pipe");
                opt->return_val = 1;
                exit(1);
            }

            pid_t frk = fork();
            switch (frk) {
            case -1:
                perror("Failed to fork");
                opt->return_val = 1;
                exit(1);
                break;
            case 0:
                if (setpgid(0, opt->child_pgid)) {
                    perror("Failed to set child's process group");
                    opt->return_val = 1;
                    exit(1);
                }                
                
                // Handles dup2 with stdout and pipe
                if (dup2(new_pipe[PIPE_WRITE], STDOUT_FILENO) == -1) {
                    perror("Failed to dup2");
                    opt->return_val = 1;
                    exit(1);
                }
                close(new_pipe[PIPE_READ]);
                close(new_pipe[PIPE_WRITE]);

                // Avoid memory leaks
                // The sub_dir is safe in memory beause it's not in the queue
                free_queue_and_data(dir_q);
                free_queue_and_data(pipe_q);

                // Exec
                exec_next_dir(sub_dir, opt);
                perror("Failed to exec to the next sub directory");
                opt->return_val = 1;
                exit(1);
            default:
                free(sub_dir);
                break;
            }
        }
}

/**
 * @brief Reads all the contents from the pipes and waits for all childs to terminate
 * 
 * @param cur_dir 
 * @param pipe_q 
 * @param opt 
 */
static void read_wait_childs(FileInfo *cur_dir, Queue_t *pipe_q, Options *opt) {
    FileInfo received_file;
    int num_childs = queue_size(pipe_q);
    int termination_status = 0, waited = 0;
    pid_t any = -1;

    errno = 0; // Set default so it won't break on the first if statement of the loop
    while (num_childs > 0 || !queue_is_empty(pipe_q)) {

        if ((waited = waitpid(any, &termination_status, WNOHANG)) > 0) {

            --num_childs;

            if (errno != ECHILD && errno != 0 && errno != EINTR) {
                perror("Error on waitpid");
                opt->return_val = 1;
                exit(1);
            }
            
            if (termination_status != 0) {
                // fprintf(stderr, "A child has terminated unsuccessfully\n");
                opt->return_val = 1;
                termination_status = 0;
            }

        }

        // Rotate the available pipes
        if (!queue_is_empty(pipe_q)) {
            int *cur_pipe = (int*) queue_pop(pipe_q);
            int read_return = read_fileInfo(&received_file, cur_pipe[PIPE_READ]);

            if (read_return == sizeof(received_file)) {
                log_info_pipe(&received_file, RECV_PIPE);
                if (received_file.dummy) {
                    close(cur_pipe[PIPE_READ]);
                    free(cur_pipe);                    
                }
                else if (received_file.is_sub_dir) {
                    // Last message from that pipe/child
                    if (!opt->separate_dirs)
                        cur_dir->file_size += received_file.file_size;
                    received_file.is_sub_dir = false;

                    // We know it's a directory
                    handle_dir_output(&received_file, opt);

                    close(cur_pipe[PIPE_READ]);
                    free(cur_pipe);
                }
                else {
                    // There are still more messages to receive
                    if (received_file.is_dir)
                        handle_dir_output(&received_file, opt);
                    else
                        handle_file_output(&received_file, opt);
                    
                    queue_push_back(pipe_q, cur_pipe);
                }
            }
            else if (read_return == 0) {
                queue_push_back(pipe_q, cur_pipe);
            }
            else if (read_return != 0 && errno != EINTR) {
                // If it was EINTR, no data was read, so we lit fam
                perror("Desync caused the read to not have enough bytes in the pipe");
                free_queue_and_data(pipe_q);
                opt->return_val = 1;
                exit(1);
            }
        }
    }
}

/**
 * @brief For each file received, it prints the file information i.e size.  
 * 
 * @param opt Options given as parameters
 * @param name Name of the file in the folder
 * @return lont int The file's size upon success, -1 otherwise
 */
static long int analyze_file(Options* opt, char *name, Queue_t *queue){
    struct stat st; 
    
    FileInfo fi;
    fi.file_size = 0;
    fi.is_sub_dir = false;
    fi.is_dir = false;
    fi.dummy = false;
    fi.name[0] = '\0';

    //get the complete path of the file called "name"
    strncpy(fi.name, opt->path, MAX_PATH_SIZE);
    if (fi.name[strlen(fi.name) - 1] != '/')
        strcat(fi.name, "/");
    strncat(fi.name, name, MAX_PATH_SIZE);

    if (lstat(fi.name, &st) < 0){
        perror("Error getting the file's stat struct");
        opt->return_val = 1;
        exit(1); 
    }

    if (S_ISLNK(st.st_mode) && !opt->dereference) {
        // Don't follow symbolic link
        fi.file_size = get_size(&st, opt);
        handle_file_output(&fi, opt);
        return fi.file_size;
    }
    else {
        if (S_ISLNK(st.st_mode)) {
            // If it was a symlink and wee have to dereference it
            // We stat the file it points to instead
            if (stat(fi.name, &st) < 0) {
                if (errno != ENOENT && errno != ELOOP) {
                    perror("Error getting the file's stat struct");
                    opt->return_val = 1;
                    exit(1);
                }
                else {
                    // Just like du, print to stderr, but keep going!
                    fprintf(stderr, "simpledu: cannot access '%s'\n", fi.name);
                    opt->return_val = 1;
                    return -1;
                }
            }
        }

        if (S_ISREG(st.st_mode)) {
            fi.file_size = get_size(&st, opt);
            handle_file_output(&fi, opt);
            return fi.file_size;
        }
        else if (S_ISDIR(st.st_mode) && strcmp(name, "..")) {
            if (strcmp(name, ".")) {
                // If it's not a '.' file
                // ADD TO QUEUE
                size_t len = strlen(fi.name) + 1;
                char *new_path = (char*) malloc(len * sizeof(char));
                strncpy(new_path, fi.name, len);
                queue_push_back(queue, new_path);

                return 0;
            }
            else {
                // It's the directory itself ('.')
                fi.file_size = get_size(&st, opt);
                return fi.file_size;
            }
        }
        else if (S_ISFIFO(st.st_mode)) {
            fi.file_size = get_size(&st, opt);
            handle_file_output(&fi, opt);
            return fi.file_size;
        }
    }

    return 0;
}

int showDirec(Options * opt) {
    DIR * direc;
    struct dirent * dirent;

    FileInfo cur_dir;
    cur_dir.is_sub_dir = true;
    cur_dir.is_dir = true;
    cur_dir.file_size = 0;
    cur_dir.dummy = false;
    strncpy(cur_dir.name, opt->path, MAX_PATH_SIZE);

    Queue_t *dir_q = new_queue();
    if (dir_q == NULL) {
        perror("Failed to instanteate the queue");
        opt->return_val = 1;
        exit(1);
    }

    if ((direc = opendir(opt->path)) == NULL){  
        perror("Not possible to open directory");
        opt->return_val = 1;
        exit(1);
    }

    // Take care of all regular files and save our directories for later
    long int tmp;
    while((dirent = readdir(direc)) != NULL){
        if (tmp = analyze_file(opt, dirent->d_name, dir_q), tmp != -1)
            cur_dir.file_size += tmp;
    }

    if (closedir(direc) == -1){
        perror("Not possible to close directory\n");
        return 1;
    }

    if (!queue_is_empty(dir_q)) {
        
        Queue_t *pipe_q = new_queue();
        if (pipe_q == NULL) {
            perror("Failed to create the pipe queue");
            opt->return_val = 1;
            exit(1);
        }

        // Launch all childs/subdirectories
        launch_dirs(dir_q, pipe_q, opt);        
        free_queue_and_data(dir_q);

        // Read and wait for all childs
        read_wait_childs(&cur_dir, pipe_q, opt);
        free_queue_and_data(pipe_q);
    }

    log_entry(&cur_dir, opt);

    if (opt->original_process) 
        print_fileInfo(&cur_dir, opt);
    
    else {
        write_fileInfo(&cur_dir, STDOUT_FILENO); 
        opt->sent_pipe_terminator = true;
        log_info_pipe(&cur_dir, SEND_PIPE);
    }

    return 0;
}
