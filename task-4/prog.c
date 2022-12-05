#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int tmp = open(argv[1], O_WRONLY | O_CREAT);//, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    // write()

    dup2(tmp, 2);

    close(tmp);
}