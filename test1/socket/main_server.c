#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include "log.h"

#define MAX_LISTEN_NUM 10
#define MAX_RCV_BYTE_NUM 512

void * readFunc(void *arg)
{
    int fd = *((int *)arg);
    char *rvmsg = (char *)malloc(sizeof(char)*MAX_RCV_BYTE_NUM);
    ssize_t realLen;
    for (;;)
    {
        memset(rvmsg, 0, sizeof(char)*MAX_RCV_BYTE_NUM);
        //recv(newfd, rvmsg, 100, MSG_WAITALL);
        rvmsg[MAX_RCV_BYTE_NUM - 1] = '\0';
        realLen = read(fd, rvmsg, sizeof(char)*MAX_RCV_BYTE_NUM);
        if (realLen == -1)
        {
            LOG("read data failed!\n");
            break;
        }
        if (realLen == 0)
        {
            LOG("client has been closed!\n");
            break;
        }
        
        rvmsg[realLen - 1] = '\0';
        LOG("recevice data: %s, %d\n", rvmsg, realLen);
    }
    free(rvmsg);
    return NULL;
}

void *writeFunc(void *arg)
{   
    int fd = *((int *)arg);
    char *msg = (char *)malloc(sizeof(char)*MAX_RCV_BYTE_NUM);

    for (;;)
    {
        memset(msg, 0, sizeof(char)*MAX_RCV_BYTE_NUM);
        fgets(msg, sizeof(char)*MAX_RCV_BYTE_NUM, stdin);
        msg[MAX_RCV_BYTE_NUM - 1] = '\0';
        if (send(fd, msg, sizeof(msg), MSG_NOSIGNAL) == -1)
        {
            LOG("send data failed!\n");
            if (errno == EPIPE)
            {
                LOG("client has closed!\n");
                break;
            }
        }
    }
    
    free(msg);
    return NULL;
}

void childProcessSocket(int fd)
{
    pthread_t readThread, writeThread;
    pthread_create(&readThread, NULL, readFunc, &fd);
    pthread_create(&writeThread, NULL, writeFunc, &fd);
    pthread_join(readThread, NULL);
    pthread_join(writeThread, NULL);
}

static void sigChildHandler(int signo)
{
    pid_t childPid;
    int saveErrno;
    saveErrno = errno;

    while ((childPid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        LOG("child process %d exit!\n", childPid);
    }

    if ( childPid == -1 && errno != ECHILD)
    {
        LOG("waitpid failed!\n");
    }
    
    errno = saveErrno;
}

void registerSigHandler()
{
    struct sigaction act;
    act.sa_handler = sigChildHandler;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    if (sigaction(SIGCHLD, &act, NULL))
    {
        LOG("regist sigchild handler failed!\n");
        return;
    }
    LOG("regist sigchild handler success!\n");
}

int main(int argc, char *argv[])
{
    struct sockaddr_in svSock;
    memset(&svSock, 0, sizeof(svSock));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    svSock.sin_family = AF_INET;
    svSock.sin_port = htons(12345);
    svSock.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(sockfd, &svSock, sizeof(svSock)) == -1)
    {
        LOG("bind failed!\n");
        return 0;
    }
    if (listen(sockfd, MAX_LISTEN_NUM) == -1)
    {
        LOG("listen server socket failed!\n");
        return 0;
    }
    struct sockaddr_in clAddr;
    memset(&clAddr, 0, sizeof(clAddr));
    socklen_t clientSockLen = sizeof(clAddr);
    
    registerSigHandler();

    LOG("waiting accept...\n");
    for (;;)
    {
        int newfd = accept(sockfd, &clAddr, &clientSockLen);
        if (newfd == -1)
        {
            LOG("accept server socket failed!\n");
            close(newfd);
            continue;
        }

        pid_t newChild = fork();
        switch (newChild)
        {
        case -1: 
            LOG("create child process failed!\n");
            close(newfd);
            break;
        case 0:
            childProcessSocket(newfd);
            close(newfd);
            close(sockfd);
            _exit(0);
            break;
        default:
            LOG("客户已接入(IP: %s, PID: %d, %s)\n", inet_ntoa(clAddr.sin_addr), newChild, currTime("%F %T %p"));
            close(newfd);
            break;
        }
    }

    close(sockfd);
    return 0;
}