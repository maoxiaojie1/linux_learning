#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    for (size_t i = 0; i < 3; i++)
    {
        printf("Hello Word!\n");
        sleep(1);
    }
    printf("child pid %d, ppid %d, grp %d\n", getpid(), getppid(), getpgrp());
    _exit(0);
    return 0;
}