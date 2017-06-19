// "Writting a debugger" workshops lead by Disconnect3d (https://disconnect3d.pl/)
// Organized thx to KNI Kernel students circle at AGH UST, Cracow, Poland
#include <stdio.h>
#include <stdarg.h>

// C POSIX library headers  // See:     // e.g. for wait(2) use `man 2 wait`
#include <unistd.h>         // unistd(0p)
#include <sys/wait.h>       // wait(2)
#include <sys/ptrace.h>     // ptrace(2)

void msg(const char* format, ...) {
    va_list ap;
    fprintf(stdout, "[%d] ", getpid());
    va_start(ap, format);
    vfprintf(stdout, format, ap);
    va_end(ap);
}

void run_debugger(pid_t children_pid) {
    msg("Running debugger with child=%d\n", children_pid);

    int wstatus;
    wait(&wstatus);
    msg("wstatus = %d\n", wstatus);
}

void run_children() {
    ptrace(PTRACE_TRACEME, 0, 0, 0);

    char* argv[] = {"/bin/ls", NULL};

    int result = execv(argv[0], argv);
    if (result == -1)
        perror("Children faild");
}

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1;
    }

    if (pid)
        run_debugger(pid);
    else
        run_children();

    return 0;
}
