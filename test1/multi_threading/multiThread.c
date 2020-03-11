#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

static int count = 0;
static pthread_mutex_t mtx; //= PTHREAD_MUTEX_INITIALIZER;
static pthread_mutexattr_t mtxattr;
void *threadFunc1(void *argv)
{
    srand(time(NULL));
    int temp = 0;
    int loop = *(int *)argv;
    for (size_t i = 0; i < loop; i++)
    {
        //printf("thread %lu: %d\n", pthread_self(), rand() % 90 + 10);
        pthread_mutex_lock(&mtx);
        temp = count;
        temp++;
        count = temp;
        pthread_mutex_unlock(&mtx);
        //printf("count = %d\n", count);
        //sleep(2);
    }
    return NULL;
}

void *threadFunc2(void *argv)
{
    srand(time(NULL));
    for (size_t i = 0; i < 10; i++)
    {
        printf("thread %lu: %d\n", pthread_self() ,rand() % 900 + 100);
        //sleep(2);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1;
    pthread_t t2;
    pthread_attr_t attr;
    int result = 0;
    int loops = 1000000;

    pthread_mutexattr_init(&mtxattr);
    pthread_attr_init(&attr);
    result = pthread_create(&t1, NULL, threadFunc1, &loops);
    if (result != 0)
    {
        printf("create thread t1 error!\n");
    }
    
    result = pthread_create(&t2, NULL, threadFunc1, &loops);
    if (result != 0)
    {
        printf("create thread t2 error!\n");
    }

    printf("main thread %lu wait t1 and t2 end!\n", pthread_self());

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("t1 and t2 threads have end!\n");
    printf("count = %d\n", count);
    return 0;
}