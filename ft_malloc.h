#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdio.h>
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

void    *ft_malloc(size_t size);

#endif