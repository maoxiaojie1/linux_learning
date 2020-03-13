#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include "log.h"

#define MAX_LISTEN_NUM 10
char *currTime(const char *format)
{
    static char buf[30];
    struct tm *ym;
    time_t sec;
    size_t s;
    sec = time(NULL);
    ym = localtime(&sec);
    s = strftime(buf, 30, format, ym);
    return (s == 0? NULL : buf);
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
    
    LOG("waiting accept...\n");
    int newfd = accept(sockfd, &clAddr, &clientSockLen);

    if (newfd == -1)
    {
        LOG("accept server socket failed!\n");
        return 0;
    }
    LOG("客户已接入(IP: %s, %s)\n", inet_ntoa(clAddr.sin_addr), currTime("%F %T %p"));

    const char msg[] = "hello world\n";
    if (send(newfd, msg, sizeof(msg), MSG_NOSIGNAL) == -1)
    {
        LOG("send data failed!\n");
        if (errno == EPIPE)
        {
            LOG("client has closed!\n");
            return 0;
        }
    }
    char *rvmsg = (char *)malloc(100);
    memset(rvmsg, 0, 100);
    //recv(newfd, rvmsg, 100, MSG_WAITALL);
    int realLen = read(newfd, rvmsg, 100);
    if (realLen == -1)
    {
        LOG("read data failed!\n");
    }
    LOG("recevice data: %s\n", rvmsg);
    free(rvmsg);
    close(newfd);
    close(sockfd);
    return 0;
}