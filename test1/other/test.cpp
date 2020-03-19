#include <iostream>
#include <unistd.h>
#include <error.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>

using namespace std;

int main(int argc, char *argv[])
{
    pid_t child_proc;
    cout << "test fork\n";
    child_proc = fork();
    if (child_proc < 0)
    {
        printf(strerror(errno));
    }
    else if (child_proc == 0)
    {
        printf("child pid %d, ppid %d, grp %d\n", getpid(), getppid(), getpgrp());
        cout << "slepp wait\n";
        sleep(2);
        execl("./hello", NULL);
        //printf("??????????");
        //_exit(0);
    }
    else
    {
        printf("parent pid %d, ppid %d, grp %d\n", getpid(), getppid(), getpgrp());
    }
    cout << "wait child\n";
    int state;
    pid_t child;
    while (!(child = waitpid(child_proc, &state, WNOHANG)))
    {
        printf("child process has not exit!\n");
        sleep(1);
    }
    //printf(strerror(errno));
    printf("child: %d, state: %d, end!\n", child, state);
    return 0;
}
