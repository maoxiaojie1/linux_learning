#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
//#include <sigaction.h>

static void sig_usr(int);
void handler(int signo);
sigjmp_buf jmpbuf;
int main(int argc, char *argv[])
{
    sigset_t osigset, sigset;
    sigemptyset(&sigset);
    //sigaddset(&sigset, SIGTERM);

    if (sigprocmask(SIG_BLOCK, &sigset, &osigset) < 0)
    {
        printf("error\n");
    }
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("can't catch SIGUSR1\n");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("can't catch SIGUSR2\n");
    }
    signal(SIGTERM, sig_usr) == SIG_ERR;
    struct sigaction newact;
    newact.sa_handler = handler;
    newact.sa_flags = 0;
    sigemptyset(&newact.sa_mask);
    if (sigaction(SIGTERM, &newact, NULL))
    {
        printf("can't catch SIGTERM\n");
    }
    int x = 0;
    if (x = sigsetjmp(jmpbuf, SIGTERM))
    {
        printf("sigsetjmp failed! %d\n", x);
        _exit(0);
    }
    printf("jmpdot!\n");
    printf("%s\n", strsignal(SIGTERM));
    for (;;)
    {
       pause();
    }
    return 0;
}

static void sig_usr(int signo)
{
    if (signo == SIGUSR1)
    {
        printf("received SIGUSR1\n");
    }
    else if (signo == SIGUSR2)
    {
        printf("received SIGUSR2\n");
    }
    else
    {
        printf("received signo: %d\n", signo);
    }
}

void handler(int signo)
{
    if (signo == SIGTERM)
    {
        printf("received SIGTERM\n");
    }
    else
    {
        printf("nothing\n");
    }
    siglongjmp(jmpbuf, SIGTERM);
}