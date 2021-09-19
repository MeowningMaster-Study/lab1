#include <stdio.h>
#include "files.h"

#include "tables/film.h"
#include "tables/cinema.h"

void insert();
void select();
void update();
void delete();

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
        }
    }
}

void create_tables() {
    film_table = create_table(FILM_FILE);
    cinema_table = create_table(CINEMA_FILE);
}

void load_tables() {
    film_table = load_table(FILM_FILE);
    cinema_table = load_table(CINEMA_FILE);
}

void close_tables() {
    close_table(&film_table);
    close_table(&cinema_table);
}

void insert() {
    char table[256];
    scanf("%s", table);

    if (!strcmp(table, "film")) {
        insert_film();
    } else if (!strcmp(table, "cinema")) {
        insert_cinema();
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
    }
}

void delete() {
    char table[256];
    unsigned id;
    scanf("%s %u", table, &id);

    if (!strcmp(table, "film")) {
        delete_film(id);
    } else if (!strcmp(table, "cinema")) {
        delete_cinema(id);
    }
}