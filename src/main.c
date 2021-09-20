#include <stdio.h>
#include "files.h"

#include "tables/film.h"
#include "tables/cinema.h"
#include "tables/session.h"

void insert();
void select();
void update();
void delete();
void stats();
void subcount();
void subselect();

void create_tables();
void load_tables();
void close_tables();

int main() {
    char command[256];

    printf("~~ Cinema database system ~~\n");
    printf("load or create database firstly!\n");
    while (1) {
        printf("> ");
        gets(command);

        if (!strcmp(command, "load")) {
            load_tables();
            break;
        } else if (!strcmp(command, "create")) {
            create_tables();
            break;
        }
    }

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (!strcmp(command, "quit")) {
            close_tables();
            return 0;
        } else if (!strcmp(command, "insert")) {
            insert();
        } else if (!strcmp(command, "select")) {
            select();
        } else if (!strcmp(command, "update")) {
            update();
        } else if (!strcmp(command, "delete")) {
            delete();
        } else if (!strcmp(command, "stats")) {
            stats();
        } else if (!strcmp(command, "subcount")) {
            subcount();
        } else if (!strcmp(command, "subselect")) {
            subselect();
        }
    }
}

void create_tables() {
    film_table = create_table(FILM_FILE);
    cinema_table = create_table(CINEMA_FILE);
    session_table = create_table(SESSION_FILE);
}

void load_tables() {
    film_table = load_table(FILM_FILE);
    cinema_table = load_table(CINEMA_FILE);
    session_table = load_table(SESSION_FILE);
}

void close_tables() {
    close_table(&film_table);
    close_table(&cinema_table);
    close_table(&session_table);
}

void insert() {
    char table[256];
    scanf("%s", table);

    if (!strcmp(table, "film")) {
        insert_film();
    } else if (!strcmp(table, "cinema")) {
        insert_cinema();
    } else if (!strcmp(table, "session")) {
        insert_session();
    }
}

void select() {
    char table[256];
    unsigned id;
    scanf("%s %u", table, &id);

    if (!strcmp(table, "film")) {
        select_film(id);
    } else if (!strcmp(table, "cinema")) {
        select_cinema(id);
    } else if (!strcmp(table, "session")) {
        select_session(id);
    }
}

void update() {
    char table[256];
    unsigned id;
    scanf("%s %u", table, &id);

    if (!strcmp(table, "film")) {
        update_film(id);
    } else if (!strcmp(table, "cinema")) {
        update_cinema(id);
    } else if (!strcmp(table, "session")) {
        update_session(id);
    }
}

void delete() {
    char table[256];
    unsigned id;
    scanf("%s %u", table, &id);

    if (!strcmp(table, "film")) {
        delete_film(id);
        delete_sessions_by_film(id);
    } else if (!strcmp(table, "cinema")) {
        delete_cinema(id);
        delete_sessions_by_cinema(id);
    } else if (!strcmp(table, "session")) {
        delete_session(id);
    }
}

void stats() {
    char table[256];
    scanf("%s", table);

    if (!strcmp(table, "film")) {
        stats_film();
    } else if (!strcmp(table, "cinema")) {
        stats_cinema();
    } else if (!strcmp(table, "session")) {
        stats_session();
    }
}

void subcount() {
    char table[256], by[256];
    unsigned id;
    scanf("%s %s %d", table, by, &id);

    if (!strcmp(table, "session")) {
        if (!strcmp(by, "film")) {
            count_sessions_by_film(id);
        } else if (!strcmp(by, "cinema")) {
            count_sessions_by_cinema(id);
        }
    }
}

void subselect() {
    char table[256], by[256];
    unsigned id;
    scanf("%s %s %d", table, by, &id);

    if (!strcmp(table, "session")) {
        if (!strcmp(by, "film")) {
            select_sessions_by_film(id);
        } else if (!strcmp(by, "cinema")) {
            select_sessions_by_cinema(id);
        }
    }
}