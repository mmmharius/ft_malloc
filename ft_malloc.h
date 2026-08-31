#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdio.h>
#include <unistd.h>

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

void    *ft_malloc(size_t size);

#endif