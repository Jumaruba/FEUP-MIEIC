# SOPE-proj1

## Brief project description

This was the code produced for SOPE's first project, whose objective was to accurately replicate linux's `du` command, taking into account only the flags `-a`, `-b`, `-B`, `-L`, `-S` and `--max-depth=`, with the flag `-l` always active.

## How to run

From the project's root directory simply run `make` to create the executable `simpledu`. Simply call `simpledu` with your intended arguments and you're ready to go!
To cleanup other files, you can also use `make clean` to delete the object files, or use `make remove` to also remove the executable.

## Features implemented

All requested features were fully implemented.
One (probable) additional feature we implemented was the flag `--apparent-size`, due to its indirect envolvement in cases such as `-b - B 512`, because it is the equivalent of `-B 1 --apparent-size -B 512`, which implicates a different behaviour from only `-B 512`.
The original `du` prints to `stdout` as much information as possible, even when encountering errors such as broken links. Although not tested by the methods used for the evaluation, we continue to print as much information as possible to `stdout`, returning 1 only at the very end.

## Known errors/bugs

When running `simpledu` on a really large folder (such asthe user's home for example), it sometimes does not output correctly. We assume this issue is related to running out of pid's, due to too many forks at once. Since synchronization hasn't been taught in class yet, we have no way to test our theory.
- Update, we may have figured this one out: Running these tests in our home involves the test script compare a run of `simpledu` and `du`, though they are always of different instants of our disk. Every single time one of these tests failed, we were running a web browser or discord on the background, which created temporary files on `~/.cache/` that were present in `simpledu` but not in `du` or vice-versa, causing random tests to fail. We also found out that this happends on `.local/ ` in the Ubuntu distro, but upon some research, that folder was introduced by GNOME/Ubuntu, and is a mix of `.config/` and `.cache/`, so it's perfectly fair the same issue described above would happen.   
TL;DR: When running tests, don't have ***anything else*** running besides that terminal. Or simply don't run tests on folders that involve the folder `.cache/` or `.local/`.

When sending a `SIGINT` to the process, aka a Ctrl+C, the signal sometimes interrupts a critical call and causes a pipe to break, cascading throughout the other processes causing `simpledu` to crash.
- Update: Since we fixed the lack of a terminator message on every pipe,  this should be fixed. 

### Behaviour on different computers

As far as we have explored, this program's behaviour doesn't differ on the various computers and linux distributions we tested (Ubuntu, Manjaro and "I use Arch btw"). These tests are elaborated upon below.

### Testing

To extensively test our `simpledu`, we developed two small bash scripts. The first runs various combinations of flags on a list of directories and tests the output (or error code) against that of `du`, using the same criteria specified in the project's guidelines. This script is called [testing.sh](src/testing.sh) and uses the auxiliary [directories](src/directories_to_test.txt) file (which should have been .gitignored a long time ago).

To complement this batch testing script, we have another one dedicated to run a single test on a single directory, calling `diff -y --suppress-common-lines` to show only the differences. We used it during development whenever a test case failed upon running the other script. This script is called [unique_testing.sh](src/unique_testing.sh).

We have tested almost every combination of flags on the following directories:
- This git's root directory
- The `Documents/` directory
- The `.config/` directory
- The user's home directory

## Implementation details

### Fork's and exec's

As requested, each subdirectory is its own process, fork'ed and exec'ed from the respective parent directory's process. Each subdiretory has its own pipe to the parent, through which they send the required information to their father (or stdout).

### Signals

With the goal of easily handling signals, and being able to send a signal to every child using only `killpg()`, we had to separate every process in two groups:
- The original process alone in a group
- The sub-directory processes and a dummy process are together in another group

In order to guarantee that every call to `setpgid()` is successful, we must ensure that group is both created and still exists. Otherwise the function would return -1 and errno would have the value `EPERM`, meaning we lacked the permissions to complete the operation.

To solve this problem, the original process creates a dummy child as soon as possible, whose sole purpuose is to outlive all the other processes. This ensures the process group leader is always active while other processes try to enter it, meaning we will never have a permissions related error. By creating this auxiliar child, we use it's pid as the process group for all our childs, as `fork()` guarantees that the child process' pid is an unused process group id.

Besides from creating the process group, this dummy also sends a char via a pipe to the original process, to garantee that the group was created before other childs attempt to join it. Afterwards it enters a while loop, with a `sleep(99)` to have it in background until the original process sends a `SIGTERM` to kill it. The original process only continues its execution after it has received the confirmation char from the dummy child.

### Pipes

Instead of recovering an open pipe by reading the `/proc` folder or playing with the fact that file descriptors remain open after an `exec`, we have chosen a more resource intensive method that also avoids problems with desynchronization upon writing to `stdout`.

Between the moment a process fork's and exec's, the child uses `dup2()` to  redirect its `stdout` to the writing end of their respective pipe. This way, when a child writes to `stdout`, that information will be sent to its father.

For this purpuose we devised a small communications protocol between all our processes using a struct. This struct contains the file (or directory)'s name and size, alonside two bools indicating wether it is a directory or a file, and if it's the "main" subdirectory. This is, if we need to add it's size to the current directory.

The needed information, wether due to subdirectory size or prints, is passed from the subdirectory process' pipe (masked as `stdout`) to their parent, and so on, until it reaches the original process, which finally prints the information, formatted, to the "real" `stdout`.

To handle the various reading ends of the childs' pipes, we used and improved upon Tiago's queue implementation developed for LCOM's final project. The pipes are taken from the queue to try to read data and then pushed back into it if there's still more data to come (our code guarantees that every pipe sends/receives at least one message, the last one having the bool `sub_dir` set to true).

### Log file's instant timestamp

As we needed to keep track of the time since the original process was launched, we had to keep track of the initial instance. The original process creates a temporary file (in the `/tmp/` folder) with the time struct written in it. All other childs access said file only once to read the initial instant's struct and use it to calculate the time passed since the start of the program.

Upon the conclusion of the original process, the temporary file is deleted.
