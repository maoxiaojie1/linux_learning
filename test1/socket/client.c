#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include "log.h"

int main(int argc, char *argv[])
{
    struct sockaddr_in svSock;
    memset(&svSock, 0, sizeof(svSock));
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    svSock.sin_family = AF_INET;
    svSock.sin_port = htons(12345);
    svSock.sin_addr.s_addr = inet_addr("127.0.0.1");

    LOG("connecting...\n");
    if (connect(sockfd, &svSock, sizeof(svSock)) == -1)
    {
        LOG("connect failed!\n");
        close(sockfd);
        return 0;
    }
    LOG("已连接服务器(%s)\n", currTime("%F %T %p"));

    char *rvmsg = (char *)malloc(100);
    memset(rvmsg, 0, 100);
    
    //recv(newfd, rvmsg, 100, MSG_WAITALL);
    int realLen = read(sockfd, rvmsg, 100);
    if (realLen == -1)
    {
        LOG("read data failed!\n");
    }
    LOG("recevice data: %s\n", rvmsg);
    free(rvmsg);

    const char msg[] = "hello world\n";
    if (send(sockfd, msg, sizeof(msg), MSG_NOSIGNAL) == -1)
    {
        LOG("send data failed!\n");
        if (errno == EPIPE)
        {
            LOG("server has closed!\n");
            return 0;
        }
    }
    close(sockfd);
    return 0;

    return 0;
}