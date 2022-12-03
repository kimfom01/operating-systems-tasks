#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    struct option longopts[] =
        {
            {.name = "number",
             .has_arg = required_argument,
             .flag = NULL,
             .val = 'n'},
            {.name = "timeout",
             .has_arg = required_argument,
             .flag = NULL,
             .val = 't'},
            {}};

    int nRepeats, tTimeout;
    char *text;

    while (1)
    {
        int c = getopt_long(argc, argv, "n:t::", longopts, NULL);

        if (c == -1)
        {
            break;
        }

        switch (c)
        {
        case 'n':
            nRepeats = atoi(optarg);
            break;
        case 't':
            if (optarg == NULL && optind < argc && argv[optind][0] != '-')
            {
                optarg = argv[optind++];
            }
            if (optarg == NULL)
            {
                tTimeout = 1;
            }
            else
            {
                tTimeout = atoi(optarg);
            }
            break;
        case '?':
            printf("usage: prntxt -n|--number <N> [-t|--timeout [<T>]] -- <TEXT>");
            return 1;
        default:
            abort();
        }
    }

    text = argv[argc - 1];

    for (int i = 0; i <= nRepeats - 1; i++)
    {
        printf("%s\n", text);
        sleep(tTimeout);
    }

    return 0;
}

// gcc prntxt.c -o prntxt && ./prntxt -n 5 -t 3 -- "Hello"
// gcc prntxt.c -o prntxt && ./prntxt -n 5 -t -- "Hello" uses default timout value
// gcc prntxt.c -o prntxt && ./prntxt -n -t 3 -- "Hello" error