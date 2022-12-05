#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        exit(-1);
    }

    char *progName = argv[1];
    char *outputFile = argv[2];
    pid_t pid = fork();
    if (pid == 0)
    {
        int tmp = open(outputFile, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        printf("Parent PID: %d\n", getppid());
        printf("Child PID: %d\n", getpid());
        dup2(tmp, 1);
        dup2(tmp, 2);

        execl(progName, progName, NULL);
        perror("execl");
        return close(tmp);
    }

    printf("Waiting for child %d ...\n", pid);

    int code;
    pid_t cpid = wait(&code);
    printf("Child %d is done with code %d\n", cpid, code);

    return 0;
}
