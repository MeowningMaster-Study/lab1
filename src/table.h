#include <stdio.h>
#include "meta.h"
#include "indexes.h"

typedef struct {
    FILE* data;
    FILE* meta;
    FILE* indexes;
} table_files;

typedef struct {
    meta_dump meta;
    indexes_dump indexes;
} table_dumps;

typedef struct {
    table_files files;
    table_dumps dumps;
} table;

table create_table(char* file_name) {
    table table;
    table.files.data = open_table(file_name, 1);
    table.files.meta = open_meta(file_name, 1);
    table.files.indexes = open_indexes(file_name, 1);
    table.dumps.meta.counter = 0;
    table.dumps.meta.size = 0;
    save_meta(table.files.meta, &table.dumps.meta);
    return table;
}

table load_table(char* file_name) {
    table table;
    table.files.data = open_table(file_name, 0);
    table.files.meta = open_meta(file_name, 0);
    table.files.indexes = open_indexes(file_name, 0);
    table.dumps.meta = load_meta(table.files.meta);
    table.dumps.indexes = load_indexes(table.files.indexes);
    return table;
}

void close_table(table* table) {
    fclose(table->files.data);
    fclose(table->files.meta);
    fclose(table->files.indexes);
}

void insert_row(table* table, void* data, size_t data_size) {
    // declare aliases
    FILE* data_file = table->files.data;
    FILE* indexes_file = table->files.indexes;
    meta_dump* meta = &table->dumps.meta;
    indexes_dump* indexes = &table->dumps.indexes;

    // write new item to the end
    fseek(data_file, meta->size * data_size, SEEK_SET);
    unsigned* id_field = (unsigned*)data;
    *id_field = meta->counter;
    fwrite(data, data_size, 1, data_file);

    // add index of new item to the dump and write it to the end
    fseek(indexes_file, meta->size * sizeof(index), SEEK_SET);
    index* index = &indexes->data[meta->size];
    index->id = meta->counter;
    index->offset = meta->size;
    fwrite(index, sizeof(index), 1, indexes_file);

    // update meta, save changes
    meta->size += 1;
    meta->counter += 1;
    save_meta(table->files.meta, meta);
    fflush(table->files.indexes);
    fflush(table->files.data);
}

void* select_row(table* table, unsigned offset, size_t data_size) {
    FILE* data_file = table->files.data;
    fseek(data_file, offset * data_size, SEEK_SET);
    void* buffer = malloc(data_size);
    fread(buffer, data_size, 1, data_file);
    return buffer;
}

void* update_row(table* table, unsigned offset, void* data, size_t data_size) {
    FILE* data_file = table->files.data;
    fseek(data_file, offset * data_size, SEEK_SET);
    fwrite(data, data_size, 1, data_file);
    fflush(data_file);
}

void delete_row(table* table, unsigned offset, size_t data_size) {
    meta_dump* meta = &table->dumps.meta;
    if (offset >= meta->size) {
        return;
    }

    indexes_dump* indexes = &table->dumps.indexes;
    if (offset != meta->size) {
        FILE* data_file = table->files.data;

        // read last item
        fseek(data_file, (meta->size - 1) * data_size, SEEK_SET);
        void* last_item = malloc(data_size);
        unsigned last_item_id = *(unsigned*) last_item;
        fread(last_item, data_size, 1, data_file);

        // read last item index
        int index_offset = find_index(indexes, meta->size, last_item_id);
        if (index_offset == -1) {
            printf("internal error: last item has no index\n");
            return;
        }
        index last_item_index = indexes->data[index_offset];

        // write last item to offset place (overwrite item to delete)
        fseek(data_file, offset * data_size, SEEK_SET);
        fwrite(&last_item, data_size, 1, data_file);
    }

    meta->size -= 1;
    save_meta(table->files.meta, meta);
}