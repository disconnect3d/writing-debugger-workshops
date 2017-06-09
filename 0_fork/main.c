// "Writting a debugger" workshops lead by Disconnect3d (https://disconnect3d.pl/)
// Organized thx to KNI Kernel students circle at AGH UST, Cracow, Poland
#include <stdio.h>

// C POSIX library headers  // See:     // e.g. for wait(2) use `man 2 wait`
#include <unistd.h>         // unistd(0p)

int main() {
    printf("main pid: %d\n", getpid());

    pid_t pid = fork();
    printf("pid=%d, getpid=%d\n", pid, getpid());
    
    return 0;
}

