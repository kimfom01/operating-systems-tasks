#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/signalfd.h>
#include <poll.h>

pid_t pid;
int finished = 0;

void handle_terminate(int signum)
{
    printf("[%d | Subprocess] Terminate\n", pid);
    finished = 1;
}

void execute_sub()
{
    // Signal interception.
    signal(SIGUSR1, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    signal(SIGTERM, handle_terminate);

    while (!finished)
    {
        kill(0, SIGUSR1);
        sleep(3);
    }
    printf("Child process with pid: %d done\n", pid);
}

void execute_main()
{
    // Signal interception.
    sigset_t sig;
    sigemptyset(&sig);
    sigaddset(&sig, SIGUSR1);
    sigaddset(&sig, SIGINT);
    sigaddset(&sig, SIGTERM);
    sigprocmask(SIG_BLOCK, &sig, NULL);
    int sigfd = signalfd(-1, &sig, 0);

    // Open the stream (freezes until the first data appears).
    printf("main with pid: %d, wait for request\n", pid);
    int requestsfd = open("requests", O_RDONLY);

    struct pollfd pfd[] = {
        {.fd = sigfd, .events = POLLIN},
        {.fd = requestsfd, .events = POLLIN}};

    while (!finished)
    {
        poll(pfd, 2, -1);

        if ((pfd[0].revents & POLLIN) != 0)
        {
            struct signalfd_siginfo siginfo = {};
            read(sigfd, &siginfo, sizeof(siginfo));

            if (siginfo.ssi_signo == SIGINT)
            {
                printf("main with pid: %d, catch SIGINT signal\n", pid);
                finished = 1;
            }
            else
            {
                printf("main with pid: %d, catch: '%s'\n", pid, strsignal(siginfo.ssi_signo));
            }
        }

        if ((pfd[1].revents & POLLIN) != 0)
        {
            char buf[16];
            int n = read(requestsfd, buf, sizeof(buf));
            if (n != 0)
            {
                printf("main with pid: %d, %.*s", pid, n, buf);
            }
        }
    }

    // Stopping the child process.
    kill(0, SIGTERM);
    close(requestsfd);

    // Waiting for it to stop.
    int code;
    wait(&code);

    printf("main with pid: %d done. Child process terminate with code: %d)", pid, code);
}

int main(int argc, char *argv[])
{
    pid = fork();
    if (pid == 0)
    {
        execute_sub();
        exit(0);
    }
    execute_main();
    exit(0);
}