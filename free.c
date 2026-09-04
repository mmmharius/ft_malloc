#include <libc.h>
#include <malloc.h>

void    free(void *ptr) {
    if (ptr == NULL)
        return;
    t_block *block_to_find = ((t_block *)ptr) - 1;
    t_zone *zone;
    t_zone *prev_zone;
    t_block *block;
    for (int i = 0; i < 3; i++) {
        prev_zone = NULL;
        zone = g_malloc.zones[i];
        while (zone != NULL) {
            block = zone->blocks;
            while(block != NULL) {
                if (block == block_to_find) {
                    if (zone->type == 2) {
                        if (prev_zone == NULL)
                            g_malloc.zones[i] = zone->next;
                        else
                            prev_zone->next = zone->next;
                        munmap(zone, zone->size);
                        return;
                    }
                    else {
                        block->free = 1;
                        return;
                    }
                }
                block = block->next;
            }
            prev_zone = zone;
            zone = zone->next;
        }
    }
}
