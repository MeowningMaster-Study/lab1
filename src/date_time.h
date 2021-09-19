#ifndef _DATE_TIME_
#define _DATE_TIME_

#include <stdio.h>

typedef struct {
    unsigned short day;
    unsigned short month;
    unsigned year;
} t_date;

typedef struct {
    unsigned short minutes;
    unsigned short hours;
} t_time;

typedef struct {
    t_date date;
    t_time time;
} t_date_time;

t_date read_date() {
    t_date res;
    printf("(dd/mm/yyyy): ");
    scanf("%u/%u/%u", &res.day, &res.month, &res.year);
    return res;
}

t_time read_time() {
    t_time res;
    printf("(hh:mm): ");
    scanf("%u:%u", &res.hours, &res.minutes);
    return res;
}

t_date_time read_date_time() {
    t_date_time res;
    printf("(dd/mm/yyyy hh:mm): ");
    scanf("%u/%u/%u %u:%u", &res.date.day, &res.date.month, &res.date.year, &res.time.hours, &res.time.minutes);
    return res;
}

void print_date(t_date date) {
    printf("%u/%u/%u", date.day, date.month, date.year);
}

#endif