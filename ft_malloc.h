#ifndef FT_MALLOC_H
#define FT_MALLOC_H

#include <stdio.h>
#include <unistd.h>

#define SIZE_ALLOC 0 // 1=TINY, 2=SMALL, 3=LARGE

void    *ft_malloc(size_t size);

#endif