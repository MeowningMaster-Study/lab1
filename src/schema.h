#include "date_time.h"

typedef struct {
    unsigned id;
    unsigned movie_id;
    unsigned cinema_id;
    date_time start;
} session;

typedef struct {
    unsigned id;
    char name[64];
} cinema;

typedef struct {
    unsigned id;
    char first_name[64];
    char last_name[64];
} actor;

typedef struct {
    unsigned id;
    unsigned film_id;
    unsigned actor_id;
} film_actor;

typedef struct {
    unsigned id;
    char name[64];
} category;

typedef struct {
    unsigned id;
    unsigned film_id;
    unsigned category_id;
} film_category;