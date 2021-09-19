#ifndef _META_
#define _META_

#include "files.h"

typedef struct {
    unsigned size;
    unsigned counter; // serves to generate unique ids
} t_meta;

t_meta load_meta(FILE* file) {
    fseek(file, 0, SEEK_SET);
    t_meta meta;
    fread(&meta, sizeof(t_meta), 1, file);
    return meta;
}

void save_meta(FILE* file, t_meta* meta) {
    fseek(file, 0, SEEK_SET);
    fwrite(meta, sizeof(t_meta), 1, file);
    fflush(file);
}

#endif