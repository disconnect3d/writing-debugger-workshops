// "Writting a debugger" workshops lead by Disconnect3d (https://disconnect3d.pl/)
// Organized thx to KNI Kernel students circle at AGH UST, Cracow, Poland
#include <stdio.h>

// C POSIX library headers  // See:     // e.g. for wait(2) use `man 2 wait`
#include <unistd.h>         // unistd(0p)
#include <sys/wait.h>       // wait(2)
#include <sys/ptrace.h>     // ptrace(2)

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid) {          // parent
        wait(NULL);     // wait for the children
    }

    else {              // children
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        int result = execv("/bin/ls", NULL);

        printf("Program %s returned %d\n", argv[0], result);
    }

    return 0;
}

