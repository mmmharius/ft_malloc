#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>
#include <sys/mman.h> //mmap

typedef struct s_block {
    size_t          size;
    int             free;
    struct s_block  *prev;
    struct s_block  *next;
} t_block;

typedef struct s_zone {
    int             type;
    size_t          size;
    struct s_zone   *next;
    struct s_block  *blocks;
}   t_zone;

typedef struct s_malloc_data {
    t_zone *zones[3]; // zones[0] = tiny, zones[1] = small, zones[2] = large
} t_malloc_data;

extern t_malloc_data g_malloc;

void    *malloc(size_t size);
void    free(void *ptr);
void    *realloc(void *ptr, size_t size);
t_block *find_space(int type, size_t size);
void    split_block(t_block *block, size_t size);
t_zone  *create_zone(int type, size_t size);
int     get_alloc_size(size_t size);

#endif