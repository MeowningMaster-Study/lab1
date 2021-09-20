#ifndef _SESSION_
#define _SESSION_

#include "../table.h"
#include "../date_time.h"
#include "film.h"
#include "cinema.h"

typedef struct {
    unsigned id;
    unsigned film_id;
    unsigned cinema_id;
    t_date_time start;
} t_session;

t_table session_table;

typedef struct {
    int success;
    t_session session;
} t_read_session_result;

t_read_session_result read_session() {
    t_read_session_result res;
    printf("film id: ");
    scanf("%u", &res.session.film_id);
    int film_index_offset = find_index(film_table.dumps.indexes, film_table.dumps.meta.size, res.session.film_id);
    if (film_index_offset == -1) {
        printf("no such film!\n");
        res.success = 0;
        return res;
    }
    printf("cinema id: ");
    scanf("%u", &res.session.cinema_id);
    int cinema_index_offset = find_index(cinema_table.dumps.indexes, cinema_table.dumps.meta.size, res.session.cinema_id);
    if (cinema_index_offset == -1) {
        printf("no such cinema!\n");
        res.success = 0;
        return res;
    }
    printf("start ");
    res.session.start = read_date_time();
    res.success = 1;
    return res;
}

void print_session(t_session* session) {
    printf("film id: %u\n", session->film_id);
    printf("cinema id: %u\n", session->cinema_id);
    printf("start: ");
    print_date_time(session->start);
    printf("\n");
}

void insert_session() {
    t_read_session_result read_result = read_session();
    if (read_result.success) {
        insert_row(&session_table, &read_result.session, sizeof(t_session));
    }
}

void select_session(unsigned id) {
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    int index_offset = find_index(indexes, meta->size, id);
    if (index_offset == -1) {
        printf("no such session!\n");
        return;
    }
    t_index select_index = indexes[index_offset];
    t_session* selected_session = (t_session*)select_row(&session_table, select_index.offset, sizeof(t_session));
    print_session(selected_session);
    free(selected_session);
}

void update_session(unsigned id) {
    int index_offset = find_index(session_table.dumps.indexes, session_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("no such session!\n");
        return;
    }
    t_index update_index = session_table.dumps.indexes[index_offset];
    t_read_session_result read_result = read_session();
    if (read_result.success) {
        update_row(&session_table, update_index.offset, &read_result.session, sizeof(t_session));
    }
}

void delete_session(unsigned id) {
    int index_offset = find_index(session_table.dumps.indexes, session_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("no such session!\n");
        return;
    }
    t_index delete_index = session_table.dumps.indexes[index_offset];
    delete_row(&session_table, delete_index.offset, index_offset, sizeof(t_session));
}

void delete_sessions_by_film(unsigned film_id) {
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->film_id == film_id) {
            delete_row(&session_table, offset, i, sizeof(t_session));
            i -= 1;
        }
        free(selected_session);
    }
}

void delete_sessions_by_cinema(unsigned cinema_id) {
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->cinema_id == cinema_id) {
            delete_row(&session_table, offset, i, sizeof(t_session));
            i -= 1;
        }
        free(selected_session);
    }
}

void count_sessions_by_film(unsigned film_id) {
    unsigned counter = 0;
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->film_id == film_id) {
            counter += 1;
        }
        free(selected_session);
    }
    printf("sessions of this film: %d\n", counter);
}

void count_sessions_by_cinema(unsigned cinema_id) {
    unsigned counter = 0;
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->cinema_id == cinema_id) {
            counter += 1;
        }
        free(selected_session);
    }
    printf("sessions in this cinema: %d\n", counter);
}

void select_sessions_by_film(unsigned film_id) {
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->film_id == film_id) {
            printf("// session %d\n", indexes[i].id);
            print_session(selected_session);
        }
        free(selected_session);
    }
}

void select_sessions_by_cinema(unsigned cinema_id) {
    t_meta* meta = &session_table.dumps.meta;
    t_indexes indexes = session_table.dumps.indexes;
    size_t i;
    for (i = 0; i < meta->size; i += 1) {
        unsigned offset = indexes[i].offset;
        t_session* selected_session = (t_session*)select_row(&session_table, offset, sizeof(t_session));
        if (selected_session->cinema_id == cinema_id) {
            printf("// session %d\n", indexes[i].id);
            print_session(selected_session);
        }
        free(selected_session);
    }
}

void stats_session() {
    stats_table(&session_table);
}

#endif