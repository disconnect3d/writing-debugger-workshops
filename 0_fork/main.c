#include <stdio.h>

#include <unistd.h>  // non C standard header, see `man unistd.h` or `man 2 fork`

int main() {
    printf("main pid: %d\n", getpid());

    pid_t pid = fork();
    printf("pid=%d, getpid=%d\n", pid, getpid());
    
    return 0;
}

