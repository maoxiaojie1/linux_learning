#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
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
    LOG("客户已接入(IP: %s, time: %s)：", inet_ntoa(clAddr.sin_addr), currTime("%F %T %p"));

    close(newfd);
    close(sockfd);
    return 0;
}