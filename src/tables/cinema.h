#include "../table.h"

typedef struct {
    unsigned id;
    char name[64];
} t_cinema;

t_table cinema_table;

t_cinema read_cinema() {
    t_cinema res;
    printf("name: ");
    scanf("\n");
    gets(res.name);
    return res;
}

void print_cinema(t_cinema* cinema) {
    printf("title: %s\n", cinema->name);
}

void insert_cinema() {
    t_cinema new_cinema = read_cinema();
    insert_row(&cinema_table, &new_cinema, sizeof(t_cinema));
}

void select_cinema(unsigned id) {
    t_meta* meta = &cinema_table.dumps.meta;
    t_indexes indexes = cinema_table.dumps.indexes;
    int index_offset = find_index(indexes, meta->size, id);
    if (index_offset == -1) {
        printf("error: no such cinema\n");
        return;
    }
    t_index select_index = indexes[index_offset];
    t_cinema* selected_cinema = (t_cinema*)select_row(&cinema_table, select_index.offset, sizeof(t_cinema));
    print_cinema(selected_cinema);
    free(selected_cinema);
}

void update_cinema(unsigned id) {
    int index_offset = find_index(cinema_table.dumps.indexes, cinema_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such cinema\n");
        return;
    }
    t_index update_index = cinema_table.dumps.indexes[index_offset];
    t_cinema new_cinema = read_cinema();
    update_row(&cinema_table, update_index.offset, &new_cinema, sizeof(t_cinema));
}

void delete_cinema(unsigned id) {
    int index_offset = find_index(cinema_table.dumps.indexes, cinema_table.dumps.meta.size, id);
    if (index_offset == -1) {
        printf("error: no such cinema\n");
        return;
    }
    t_index delete_index = cinema_table.dumps.indexes[index_offset];
    delete_row(&cinema_table, delete_index.offset, index_offset, sizeof(t_cinema));
}