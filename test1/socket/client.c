#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include "log.h"

int main(int argc, char *argv[])
{
    /*struct sockaddr_in clSock;
    int fd = open("./tt", O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0)
    {
        return 0;
    }
    //int stdout_fd = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    const char str[] = "llokjjk\n";
    int num = write(fd, str, sizeof(str));
    printf("Ssssss\n");
    fflush(stdout);
    //close(fd);
    //int stdout_fd = dup(STDOUT_FILENO);
    //dup2(STDOUT_FILENO, fd);
    //fdopen(1, 'rb+');
    int ttyfd = open("/dev/tty", O_RDWR, 0644);
    dup2(ttyfd, STDOUT_FILENO);
    printf("ppppppp\n");*/
    FILE *fp;
    fp = fopen("./phs_test_used_log.txt", "a+");
    fputs("pplpkpk\n", fp);
    fclose(fp);
    LOG("ff\n");
    const char *str = "";
    printf("end:%cdd", ' ');
    sleep(10);
    printf("ccsdasda\n");

    return 0;
}