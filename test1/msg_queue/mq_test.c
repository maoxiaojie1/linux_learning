#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>

#define MQ_NAME "/mqueue_test"

void threadFunc1(__sigval_t val)
{
    mqd_t mqd = *(mqd_t*)val.sival_ptr;
    char msg[20] = {0};

    mq_receive(mqd, msg, 20, NULL);
    printf("%s\n", msg);
}

int main(int argc, char *argv[])
{
    mqd_t mqd;
    mqd = mq_open(MQ_NAME, O_CREAT|O_EXCL|O_RDWR);

    struct sigevent notifaction;
    notifaction.sigev_notify = SIGEV_THREAD;
    notifaction._sigev_un._sigev_thread._function = threadFunc1;
    notifaction.sigev_value.sival_ptr = &mqd;

    mq_notify(mqd, &notifaction);

    char msg[] = "hello world!";
    mq_send(mqd, msg, sizeof(mqd), 0);
    pause();
    mq_unlink(MQ_NAME);
    return 0;
}