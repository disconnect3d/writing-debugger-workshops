// "Writting a debugger" workshops lead by Disconnect3d (https://disconnect3d.pl/)
// Organized thx to KNI Kernel students circle at AGH UST, Cracow, Poland
#include <stdio.h>

// C POSIX library headers  // See:     // e.g. for wait(2) use `man 2 wait`
#include <unistd.h>         // unistd(0p)
#include <sys/wait.h>       // wait(2)

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
        char* py_code = "import time; print('start sleep'); time.sleep(2); print('end sleep')";
        char* argv[] = {"/usr/bin/env", "python", "-c", py_code, NULL};

        int result = execv(argv[0], argv);
        
        // When does it print?
        perror("execv");
        printf("Program %s returned %d\n", argv[0], result);
    }

    return 0;
}

