#include "../date_time.h"
#include "../table.h"

typedef struct {
    unsigned id;
    char title[64];
    char description[256];
    date release_date;
    unsigned length;
    unsigned short rating;
} film;

table film_table;

film read_film() {
    film res;
    printf("title: ");
    scanf("\n");
    gets(res.title);
    printf("description: ");
    gets(res.description);
    printf("release date ");
    res.release_date = read_date();
    printf("length: ");
    scanf("%u", &res.length);
    printf("rating: ");
    scanf("%u", &res.rating);
    return res;
}

void print_film(film* film) {
    printf("title: %s\n", film->title);
    printf("description: %s\n", film->description);
    printf("release date ");
    print_date(film->release_date);
    printf("\n");
    printf("length: %u\n", film->length);
    printf("rating: %u\n", film->rating);
}

void insert_film() {
    film new_film = read_film();
    insert_row(&film_table, &new_film, sizeof(film));
}

void select_film(unsigned id) {
    int index_offset = find_index(&film_table.dumps.indexes, film_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    index select_index = film_table.dumps.indexes.data[index_offset];
    film* selected_film = (film*)select_row(&film_table, select_index.offset, sizeof(film));
    print_film(selected_film);
    free(selected_film);
}

void update_film(unsigned id) {
    int index_offset = find_index(&film_table.dumps.indexes, film_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    index update_index = film_table.dumps.indexes.data[index_offset];
    film new_film = read_film();
    update_row(&film_table, update_index.offset, &new_film, sizeof(film));
}

void delete_film(unsigned id) {
    int index_offset = find_index(&film_table.dumps.indexes, film_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    index delete_index = film_table.dumps.indexes.data[index_offset];
    delete_row(&film_table, delete_index.offset, sizeof(film));
}