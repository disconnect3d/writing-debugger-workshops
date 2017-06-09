// "Writting a debugger" workshops lead by Disconnect3d (https://disconnect3d.pl/)
// Organized at KNI Kernel students assoc. at AGH UST, Cracow, Poland
#include <stdio.h>
#include <stdlib.h>

// C POSIX library headers  // See:
#include <unistd.h>         // unistd.h(0p)
#include <sys/wait.h>

// Communicate between parent & children
// See pipe(3p) for an easier example (just sending data from parent to children)

// File descriptors for piping output
#define P1_READ     0
#define P2_WRITE    1
#define P2_READ     2
#define P1_WRITE    3
int fds[4];

void parent();
void children();

int main() {
    if (pipe(fds) == -1 || pipe(fds+2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    switch (fork()) {
        case -1:                    // handle error
            perror("fork failed");
            exit(EXIT_FAILURE);

        case 0:                     // children
            children();
            exit(EXIT_SUCCESS);

        default:                    // parent
            parent();
            exit(EXIT_SUCCESS);
    }

    return 0;
}


#define BUF_SIZE 256

void parent() {
    pid_t pid = getpid();

    // Start by closing descriptors we don't need in parent
    close(fds[P2_READ]);
    close(fds[P2_WRITE]);

    char buf[BUF_SIZE];

    // sending
    printf("Parent(%d): sending hello\n", pid);
    sprintf(buf, "Hello from parent(%d)", getpid());
    write(fds[P1_WRITE], buf, BUF_SIZE);   // see NOTE below

    // receiving
    read(fds[P1_READ], buf, BUF_SIZE);
    printf("Parent(%d): received: %s\n", pid, buf);
    
    // close remaining descriptors
    close(fds[P1_READ]);
    close(fds[P1_WRITE]);

    // wait for children termination
    wait(NULL);
}

void children() {
    pid_t pid = getpid();

    // Start by closing descriptors we don't need in children
    close(fds[P1_READ]);
    close(fds[P1_WRITE]);

    char buf[BUF_SIZE];

    // receiving
    read(fds[P2_READ], buf, BUF_SIZE);    // see NOTE below
    printf("Child(%d) received: %s\n", pid, buf);

    // sending
    printf("Child(%d): sending hello back\n", pid);
    sprintf(buf, "Hello from children(%d)", getpid());
    write(fds[P2_WRITE], buf, BUF_SIZE);
    
    close(fds[P2_READ]);
    close(fds[P2_WRITE]);
}

/*
    NOTE: read and write calls aren't made properly above
    as they might not read or write the count we provide it.

    It has been written as it is for simplicity.
    
    A proper error handled `write` call would look like this:

        size_t written = 0;
        while(written != count) {
            ssize_t result = write(fds[1], buf+written, BUF_SIZE-written);
            if (result == -1) {
                perror("write");
                // HANDLE ERROR...
            }
            written += result;
        }
*/    
