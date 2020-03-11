#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
void test_pipe_write_and_read();
void test_pipe_sync_proc();
int main(int argc, char *argv[])
{
    //test_pipe_write_and_read();
    test_pipe_sync_proc();
    return 0;
}

void test_pipe_write_and_read()
{
    pid_t childId;
    int fd[2], fd_pipe;
    fd_pipe = pipe(fd);
    if ((childId = fork()) < 0)
    {
        printf("fork error!\n");
        _exit(0);
    }
    else if (childId == 0)
    {
        char str[20];
        printf("child process!\n");
        if (close(fd[0]) == -1)
        {
            printf("close fd[0] failed!\n");
        };
        for (;;)
        {
            int i = 0;
            memset(str, 0, sizeof(str));
            while((str[i] = getchar())!='\n')
                i++;
            write(fd[1], str, strlen(str));
            //write(STDOUT_FILENO, str, i + 1);
        }
        close(fd[1]);
        _exit(0);
    }
    else
    {
        char str1[20];
        ssize_t numRead;
        if (close(fd[1]) == -1)
        {
            printf("close fd[1] failed!\n");
        };
        for (;;)
        {
            memset(str1, 0, sizeof(str1));
            numRead =  read(fd[0], str1, 20);
            write(STDOUT_FILENO, str1, strlen(str1));
            //write(STDOUT_FILENO, "\n", 1);
            //printf("parent read: %d, %s\n", numRead, str1);
        }
        wait(NULL);
        close(fd[0]);
        exit(0);
    }
}

void test_pipe_sync_proc()
{
    static const unsigned int childNum = 2;
    pid_t child[childNum];
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("creat pipe failed\n");
    }
    for (size_t i = 0; i < childNum; i++)
    {
        child[i] = fork();
        int flag = 0;
        switch (child[i])
        {
        case -1:
            printf("fork child %lu failed!\n", i);
            break;
        case 0:
            sleep(1);
            close(fd[0]);
            flag = close(fd[1]);
            printf("child %lu (pid = %d) close pipe write (fd[1]) %s\n", i, getpid(), flag == -1? "failed":"success");
            _exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
    char dumy = '\0';
    close(fd[1]);
    printf("wait child proc exit!\n");
    read(fd[0], &dumy, 1);
    sleep(1);
    printf("all child proc have success exit!\n");
    exit(EXIT_SUCCESS);
}