#include <alloca.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>

char *currTime(const char *format);

int main(){
    int *p = (int *)alloca(4);
    *p = 1;
    printf("%d\n", *p);

    struct timeval tv;
    if (0 != gettimeofday(&tv, NULL))
        printf("get time error!\n");
    printf("Seconds: %ld, Microseconds: %ld\n", tv.tv_sec, tv.tv_usec);

    time_t sec;
    printf("Seconds: %ld\n", time(&sec));
    printf("time: %s\n", ctime(&sec));

    struct tm *mm;
    mm = gmtime(&tv.tv_sec);
    printf("Seconds: %ld\n", mktime(mm));
    printf("asctime: %s\n", asctime(mm));

    printf("time: %s\n", currTime("%F %T %p"));
}

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