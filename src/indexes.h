#ifndef _INDEXES_
#define _INDEXES_

#include "files.h"

typedef struct {
    unsigned id;
    unsigned offset;
} t_index;

typedef t_index* t_indexes;

t_indexes malloc_indexes() {
    return malloc(1024 * sizeof(t_index));
}

t_indexes load_indexes(FILE* file, unsigned indexes_size) {
    fseek(file, 0, SEEK_SET);
    t_indexes indexes = malloc_indexes();
    fread(indexes, indexes_size * sizeof(t_index), 1, file);
    return indexes;
}

void insert_index(FILE* file, t_indexes indexes, unsigned offset, t_index new_index) {
    // insert to dump
    indexes[offset] = new_index;

    // insert to file
    fseek(file, offset * sizeof(t_index), SEEK_SET);
    fwrite(&new_index, sizeof(t_index), 1, file);
    fflush(file);
}

int find_index(t_indexes indexes, unsigned indexes_size, unsigned id) {
    if (indexes_size == 0) {
        return -1;
    }

    unsigned l = 0, r = indexes_size, m;
    while (l < r) {
        m = (l + r) / 2;
        if (id <= indexes[m].id) {
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

void update_index(FILE* file, t_indexes indexes, unsigned offset, unsigned new_item_offset) {
    // update dump
    indexes[offset].offset = new_item_offset;
    
    // update file
    fseek(file, offset * sizeof(t_index) + sizeof(unsigned), SEEK_SET); // seek to offset field
    fwrite(&new_item_offset, sizeof(unsigned), 1, file);
    fflush(file);
}

void delete_index(FILE* file, t_indexes indexes, unsigned indexes_size, unsigned offset) {
    // update dump
    size_t i = offset, j = offset + 1;
    while (j < indexes_size) {
        indexes[i] = indexes[j];
        i += 1;
        j += 1;
    }

    // update file
    fseek(file, offset * sizeof(t_index), SEEK_SET);
    fwrite(indexes + offset, sizeof(t_index), indexes_size - offset - 1, file);
    fflush(file);
}

#endif