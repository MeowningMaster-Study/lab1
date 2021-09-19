#include <stdio.h>
#include "files.h"

#include "tables/film.h"

void insert();
void select();

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
        }
    }
}

void create_tables() {
    film_table = create_table(FILM_FILE);
}

void load_tables() {
    film_table = load_table(FILM_FILE);
}

void close_tables() {
    close_table(&film_table);
}

void insert() {
    char table[256];
    scanf("%s", table);

    if (!strcmp(table, "film")) {
        insert_film();
    }
}

void select() {
    char table[256];
    unsigned id;
    scanf("%s %u", table, &id);

    if (!strcmp(table, "film")) {
        select_film(id);
    }
}

void update() {}