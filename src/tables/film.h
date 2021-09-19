#include "../date_time.h"
#include "../table.h"

typedef struct {
    unsigned id;
    char title[64];
    char description[256];
    t_date release_date;
    unsigned length;
    unsigned short rating;
} t_film;

t_table film_table;

t_film read_film() {
    t_film res;
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

void print_film(t_film* film) {
    printf("title: %s\n", film->title);
    printf("description: %s\n", film->description);
    printf("release date ");
    print_date(film->release_date);
    printf("\n");
    printf("length: %u\n", film->length);
    printf("rating: %u\n", film->rating);
}

void insert_film() {
    t_film new_film = read_film();
    insert_row(&film_table, &new_film, sizeof(t_film));
}

void select_film(unsigned id) {
    t_meta* meta = &film_table.dumps.meta;
    t_indexes indexes = film_table.dumps.indexes;
    int index_offset = find_index(indexes, meta->size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    t_index select_index = indexes[index_offset];
    t_film* selected_film = (t_film*)select_row(&film_table, select_index.offset, sizeof(t_film));
    print_film(selected_film);
    free(selected_film);
}

void update_film(unsigned id) {
    int index_offset = find_index(film_table.dumps.indexes, film_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    t_index update_index = film_table.dumps.indexes[index_offset];
    t_film new_film = read_film();
    update_row(&film_table, update_index.offset, &new_film, sizeof(t_film));
}

void delete_film(unsigned id) {
    int index_offset = find_index(film_table.dumps.indexes, film_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such film\n");
        return;
    }
    t_index delete_index = film_table.dumps.indexes[index_offset];
    delete_row(&film_table, delete_index.offset, index_offset, sizeof(t_film));
}