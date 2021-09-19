#ifndef _TABLE_
#define _TABLE_

#include <stdio.h>
#include "meta.h"
#include "indexes.h"

typedef struct {
    FILE* data;
    FILE* meta;
    FILE* indexes;
} t_table_files;

typedef struct {
    t_meta meta;
    t_indexes indexes;
} t_table_dumps;

typedef struct {
    t_table_files files;
    t_table_dumps dumps;
} t_table;

t_table create_table(char* file_name) {
    t_table table;
    table.files.data = open_table(file_name, 1);
    table.files.meta = open_meta(file_name, 1);
    table.files.indexes = open_indexes(file_name, 1);
    table.dumps.meta.counter = 0;
    table.dumps.meta.size = 0;
    table.dumps.indexes = malloc_indexes();
    save_meta(table.files.meta, &table.dumps.meta);
    return table;
}

t_table load_table(char* file_name) {
    t_table table;
    table.files.data = open_table(file_name, 0);
    table.files.meta = open_meta(file_name, 0);
    table.files.indexes = open_indexes(file_name, 0);
    table.dumps.meta = load_meta(table.files.meta);
    table.dumps.indexes = load_indexes(table.files.indexes, table.dumps.meta.size);
    return table;
}

void close_table(t_table* table) {
    fclose(table->files.data);
    fclose(table->files.meta);
    free(table->dumps.indexes);
    fclose(table->files.indexes);
}

void insert_row(t_table* table, void* data, size_t data_size) {
    // declare aliases
    FILE* data_file = table->files.data;
    FILE* indexes_file = table->files.indexes;
    t_meta* meta = &table->dumps.meta;
    t_indexes indexes = table->dumps.indexes;

    // write new item to the end
    fseek(data_file, meta->size * data_size, SEEK_SET);
    unsigned* id_field = (unsigned*)data;
    *id_field = meta->counter;
    fwrite(data, data_size, 1, data_file);

    // add index of new item to the dump and write it to the end
    t_index new_index;
    new_index.id = meta->counter;
    new_index.offset = meta->size;
    insert_index(indexes_file, indexes, meta->size, new_index);

    // update meta, save changes
    meta->size += 1;
    meta->counter += 1;
    save_meta(table->files.meta, meta);
    fflush(table->files.data);
}

void* select_row(t_table* table, unsigned offset, size_t data_size) {
    FILE* data_file = table->files.data;
    fseek(data_file, offset * data_size, SEEK_SET);
    void* buffer = malloc(data_size);
    fread(buffer, data_size, 1, data_file);
    return buffer;
}

void* update_row(t_table* table, unsigned offset, void* data, size_t data_size) {
    FILE* data_file = table->files.data;
    fseek(data_file, offset * data_size, SEEK_SET);
    fwrite(data, data_size, 1, data_file);
    fflush(data_file);
}

void delete_row(t_table* table, unsigned offset, unsigned index_offset, size_t data_size) {
    t_meta* meta = &table->dumps.meta;
    if (offset >= meta->size) {
        return;
    }

    if (offset + 1 != meta->size) {
        FILE* data_file = table->files.data;
        FILE* indexes_file = table->files.indexes;
        t_indexes indexes = table->dumps.indexes;

        // read last item
        fseek(data_file, (meta->size - 1) * data_size, SEEK_SET);
        void* last_item = malloc(data_size);
        fread(last_item, data_size, 1, data_file);
        unsigned last_item_id = *(unsigned*) last_item;

        // update indexes
        int last_item_index_offset = find_index(indexes, meta->size, last_item_id);
        if (last_item_index_offset == -1) {
            printf("internal error: last item has no index\n");
            return;
        }
        update_index(indexes_file, indexes, last_item_index_offset, offset);
        delete_index(indexes_file, indexes, meta->size, index_offset);

        // write last item to offset place (overwrite item to delete)
        fseek(data_file, offset * data_size, SEEK_SET);
        fwrite(last_item, data_size, 1, data_file);
        free(last_item);
    }

    meta->size -= 1;
    save_meta(table->files.meta, meta);
}

#endif