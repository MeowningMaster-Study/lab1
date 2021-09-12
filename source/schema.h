#include <time.h>

struct film {
    unsigned id;
    char title[64];
    char description[1024];
    time_t release_date;
    unsigned length;
    unsigned short rating;
};

struct session {
    unsigned id;
    unsigned movie_id;
    unsigned cinema_id;
    time_t start_time;
};

struct cinema {
    unsigned id;
    char name[64];
};

struct actor {
    unsigned id;
    char first_name[64];
    char last_name[64];
};

struct film_actor {
    unsigned id;
    unsigned film_id;
    unsigned actor_id;
};

struct category {
    unsigned id;
    char name[64];
};

struct film_category {
    unsigned id;
    unsigned film_id;
    unsigned category_id;
};