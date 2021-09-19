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

t_date_time read_date_time() {
    t_date_time res;
    printf("(dd/mm/yyyy hh:mm): ");
    int dd, mm, yy, h, m;
    scanf(
        "%d/%d/%d %d:%d",
        &dd, &mm, &yy, &h, &m
    );
    res.date.day = dd;
    res.date.month = mm;
    res.date.year = yy;
    res.time.hours = h;
    res.time.minutes = m;
    return res;
}

void print_date(t_date date) {
    printf("%u/%u/%u", date.day, date.month, date.year);
}

void print_date_time(t_date_time date_time) {
    printf(
        "%u/%u/%u %u:%u",
        date_time.date.day,
        date_time.date.month,
        date_time.date.year,
        date_time.time.hours,
        date_time.time.minutes
    );
}

#endif