#ifndef _FILES_
#define _FILES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char DATABASE_FOLDER[] = "db\\";
char FILM_FILE[] = "film";
char SESSION_FILE[] = "session";
char CINEMA_FILE[] = "cinema";
char ACTOR_FILE[] = "actor";
char FILM_ACTOR_FILE[] = "film_actor";
char CATEGORY_FILE[] = "category";
char FILM_CATEGORY_FILE[] = "film_category";

char* get_path(char* file_name) {
    char* path = (char*)malloc(256);
    strcpy(path, DATABASE_FOLDER);
    strcat(path, file_name);
    strcat(path, ".hex");
    return path;
}

// create also clears file
FILE* open_file(char* file_name, int create) {
    char* path = get_path(file_name);
    char atc[] = "r+b";
    if (create) {
        atc[0] = 'w';
    };
    FILE* res = fopen(path, atc);
    free(path);
    return res;
}

FILE* open_table(char* file_name, int create) {
    open_file(file_name, create);
}

FILE* open_indexes(char* file_name, int create) {
    char indexes_file[256];
    strcpy(indexes_file, file_name);
    strcat(indexes_file, "_indexes");
    return open_file(indexes_file, create);
}

FILE* open_meta(char* file_name, int create) {
    char meta_file[256];
    strcpy(meta_file, file_name);
    strcat(meta_file, "_meta");
    return open_file(meta_file, create);
}

#endif