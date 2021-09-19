#include "files.h"

typedef struct {
    unsigned id;
    unsigned offset;
} index;

typedef struct {
    index data[1024];
} indexes_dump;

indexes_dump load_indexes(FILE* file) {
    fseek(file, 0, SEEK_SET);
    indexes_dump indexes;
    fread(&indexes, sizeof(indexes_dump), 1, file);
    return indexes;
}

void insert_index(FILE* file, unsigned offset, index* data) {
    fseek(file, offset * sizeof(index), SEEK_SET);
    fwrite(data, sizeof(index), 1, file);
    fflush(file);
}

int find_index(indexes_dump* dump, unsigned indexes_size, unsigned id) {
    if (indexes_size == 0) {
        return -1;
    }
    index* indexes = dump->data;
    unsigned l = 0, r = indexes_size, m;
    while (l < r) {
        m = (l + r) / 2;
        if (indexes[m].id <= id) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    if (indexes[l].id != id) {
        return -1;
    }
    return l;
}

void update_index(FILE* file, indexes_dump* dump, unsigned indexes_size, unsigned new_offset) {

}