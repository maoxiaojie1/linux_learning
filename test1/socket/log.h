#ifndef __LOG_H_2020_3_11_16_20_
#define __LOG_H_2020_3_11_16_20_

#define LOG(fmt, ...) printf("%s(%d)-<%s>: "fmt, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#endif