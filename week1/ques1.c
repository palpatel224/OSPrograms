#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        printf("Child process: My PID is %d, My Parent's PID is %d\n", getpid(), getppid());
        printf("Child process terminating...\n");
        exit(0);
    } else {
        printf("Parent process: My PID is %d, My Child's PID is %d\n", getpid(), pid);
        wait(NULL);
        printf("Parent process: Child has terminated.\n");
    }

    return 0;
}

