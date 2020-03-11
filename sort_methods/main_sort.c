#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/unistd.h>


void selectSort(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        int min = arr[i];
        int minIndex = i;

        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                minIndex = j;
            }
        }
        
        if(i != minIndex)
        {
            arr[minIndex] = arr[i];
            arr[i] = min;
        }
    }
}

int main(int argc, char *argv[])
{
    /*srand(time(NULL));
    int arr[20];

    for (size_t i = 0; i < 20; i++)
    {
        arr[i] = rand() % 100 + 10;
        printf("%d ", arr[i]);
    }
    printf("\n");

    selectSort(arr, 20);
    for (size_t i = 0; i < 20; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");*/
    int fd = open("./tt", O_CREAT | O_RDWR | O_APPEND);
    if (fd < 0)
    {
        return 0;
    }
    int stdout_fd = dup(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    const char str[] = "llokjjk\n";
    int num = write(fd, str, sizeof(str));
    printf("Ssssss\n");
    fflush(stdout);
    close(fd);

    dup2(stdout_fd, STDOUT_FILENO);
    printf("ppppppp\n");

    return 0;
}