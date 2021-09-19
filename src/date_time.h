#include <stdio.h>

typedef struct {
    unsigned short day;
    unsigned short month;
    unsigned year;
} date;

typedef struct {
    unsigned short minutes;
    unsigned short hours;
} time;

typedef struct {
    date date;
    time time;
} date_time;

date read_date() {
    date res;
    printf("(dd/mm/yyyy): ");
    scanf("%u/%u/%u", &res.day, &res.month, &res.year);
    return res;
}

time read_time() {
    time res;
    printf("(hh:mm): ");
    scanf("%u:%u", &res.hours, &res.minutes);
    return res;
}

date_time read_date_time() {
    date_time res;
    printf("(dd/mm/yyyy hh:mm): ");
    scanf("%u/%u/%u %u:%u", &res.date.day, &res.date.month, &res.date.year, &res.time.hours, &res.time.minutes);
    return res;
}

void print_date(date date) {
    printf("%u/%u/%u", &date.day, &date.month, &date.year);
}