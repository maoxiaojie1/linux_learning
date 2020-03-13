#ifndef __LOG_H_2020_3_11_16_20_
#define __LOG_H_2020_3_11_16_20_

#define LOG(fmt, ...) printf("%s %s(%d)-<%s>: "fmt, currTime("%F %T %p"),__FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

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

#endif