#pragma once

#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

/** @brief The default block size to be used */
#define DEFAULT_BLOCK_SIZE 1024
/** @brief The offset of the number parameter in the '--block-size=N' argument */
#define BLOCK_SIZE_STR_OFFSET 13
/** @brief The offset of the number parameter in the '--max-depth=N' argument*/
#define MAX_DEPTH_STR_OFFSET 12

/** @brief Index of the input side of a pipe */
#define PIPE_READ 0
/** @brief Index of the output side of a pipe */
#define PIPE_WRITE 1

/** @brief Max size of pipe */
#define MAXLINE 4096

#define MAX_PATH_SIZE 512

#define MAX_PATH_SIZE_CHECKED (MAX_PATH_SIZE - 100)

/**
 * @brief Struct to keep track of the simpledu parameters to be used\n
 * Also has a couple of extra things
 * @details The default parameters are:\n
 * \tblock_size = DEFAULT_BLOCK_SIZE\n
 * \tpath = "."\n
 * \tThe other bools are false\n
 * depth_val should only be used when max_depth is set to true
 */

typedef struct fileInfo {
    long int file_size;
    bool is_sub_dir, is_dir, dummy;
    char name[MAX_PATH_SIZE];
} FileInfo;


typedef struct cmd_options {
    char *program_name;
    bool original_process;                   /** @brief True if it's the original process */

    bool all, dereference, separate_dirs, max_depth, apparent_size; 
    long block_size;
    int depth_val;
    char *path;
    
    int return_val; // Used for the case of broken symlinks

    bool sent_pipe_terminator;

    pid_t child_pgid;
    bool sig_termed_childs;
} Options;

/**
 * @brief Handles everything the program needs to start
 * 
 * @param argc 
 * @param argv 
 * @param opt 
 */
void simpledu_startup(int argc, char *argv[], Options *opt);

/**
 * @brief Returns wether a string is a number or not
 * 
 * @param s Pointer to the string to analyse, must be null terminated
 * @return true If the string is only made of numbers and is not an empty string
 * @return false Otherwise
 */
bool is_num(char *s);

/**
 * @brief Get the num digits of a number
 * 
 * @param n 
 * @return int 
 */
int get_num_digits(long int n);

/**
 * @brief Prints the saved configuration of the simpledu command stored on the Options struct
 * 
 * @param opt Pointer to the Options struct to print
 */
void print_options(Options *opt);


// Flags:
// a (all), b (bytes), -L (dereference), S (separate-dirs)
// B (block-size=), max-depth=N
/**
 * @brief Parses the given command line arguments into a more handy Options struct
 * 
 * @param argc Number of cmd line arguments
 * @param argv Array of the arguments
 * @param opt Pointer to the Options struct
 * @return int 0 upon succes, 1 otherwise 
 */
int parse_arguments(int argc, char *argv[], Options *opt);

/**
 * @brief Calls exec onto 
 * 
 * @param complete_path 
 * @param opt 
 * @param envp
 */

void exec_next_dir(char *complete_path, Options *opt);

/**
 * @brief Converts the argv vector to a string
 * 
 * @param argc Number of elements in argv
 * @param argv Vector to be converted
 * @param res Where the answer will be stored
 */
void argvToString(int argc, char *argv[], char* res); 