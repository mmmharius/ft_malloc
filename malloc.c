#include <libc.h>
#include <malloc.h>

t_malloc_data g_malloc = {{NULL, NULL, NULL}};

void    *malloc(size_t size) {
    int type = get_alloc_size(size);
    t_block *block;
    if (type != 2) {
        block = find_space(type, size);
        if (block != NULL)
        {
            if (block->size >= size + sizeof(t_block) + 1)
                split_block(block, size);
            block->free = 0;
            return (block + 1);
        }
    }
    t_zone *zone = create_zone(type, size);
    if (zone == NULL)
        return (perror("mmap:"), NULL); 
    zone->blocks->free = 0;
    return (zone->blocks + 1);
}


