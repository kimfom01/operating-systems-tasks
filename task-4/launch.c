#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv)
{
    __pid_t pid = fork();
    if (pid == 0)
    {
        execl("prog", "logfile", NULL);
        return 0;
    }

    printf("Waiting for child %d ...\n", pid);

    int code;
    __pid_t cpid = wait(&code);
    printf("Child %d is done with code %d\n", cpid, code);

    return 0;
}