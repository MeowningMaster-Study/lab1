#include "files.h"

typedef struct {
    unsigned size;
    unsigned counter; // serves to generate unique ids
} meta_dump;

meta_dump load_meta(FILE* file) {
    fseek(file, 0, SEEK_SET);
    meta_dump meta;
    fread(&meta, sizeof(meta_dump), 1, file);
    return meta;
}

void save_meta(FILE* file, meta_dump* meta) {
    fseek(file, 0, SEEK_SET);
    fwrite(meta, sizeof(meta_dump), 1, file);
    fflush(file);
}