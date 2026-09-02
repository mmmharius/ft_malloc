#include <libft.h>
#include <ft_malloc.h>

t_malloc_data g_malloc = {{NULL, NULL, NULL}};

t_block *find_space(int type, size_t size)
{
    t_zone  *zone;
    t_block *block;

    zone = g_malloc.zones[type];
    while (zone != NULL)
    {
        block = zone->blocks;
        while (block != NULL)
        {
            if (block->free == 1 && block->size >= (size + 64))
                return (block);
            block = block->next;
        }
        zone = zone->next;
    }
    return (NULL);
}

void split_block(t_block *block, size_t size)
{
    t_block *new_block;

    new_block = (t_block *)((char *)block + sizeof(t_block) + size);
    new_block->size = block->size - size - sizeof(t_block);
    new_block->free = 1;
    new_block->prev = block;
    new_block->next = block->next;
    if (block->next != NULL)
        block->next->prev = new_block;
    block->next = new_block;
    block->size = size;
}

t_zone *create_zone(int type, size_t size) {
    #if OS_TYPE == 1
        long page_size = sysconf(_SC_PAGESIZE);
    #elif OS_TYPE == 2
        long page_size = getpagesize(_SC_PAGESIZE);
    #else
    # warning "OS_TYPE not know ! use macOs/Linux pls"
        return 0;
    #endif
    void *ptr;
    if (type == 0) {
        ptr = mmap(NULL, 12288, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        size = 12288;
    }
    else if (type == 1) {
        ptr = mmap(NULL, 69632, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        size = 69632;
    }
    else {
        size_t nbr_page = ((size + sizeof(t_zone) + sizeof(t_block)) + page_size - 1) / page_size;
        size_t size_mmap = nbr_page * page_size;
        // printf("nbr_page: %zu, size : %zu\n", nbr_page, size);
        ptr = mmap(NULL, size_mmap, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        size = size_mmap;
        // printf("after mmap size : %zu\n", size);
    }
    if (ptr == MAP_FAILED)
        return(NULL);
    t_zone *zone = (t_zone *)ptr;
    zone->size = size;
    zone->type = type;
    t_block *first_b = (t_block *)(zone + 1); // zone + 1 -> zone + 32oct
    first_b->size = zone->size - sizeof(t_block) - sizeof(t_zone);
    first_b->free = 1;
    first_b->prev = NULL;
    first_b->next = NULL;
    zone->blocks = first_b;
    zone->next = g_malloc.zones[zone->type];
    g_malloc.zones[zone->type] = zone;
    return (zone);
}

int    get_alloc_size(size_t size) {

    if (size <= 90) // 32 + ( (90 + 32) * 100 ) = 12232 (56oct lost: 4096x3 = 12288);
        return 0;
    if (size <= 664) // 32 + ( (664 + 32 ) * 100 ) = 69632 (4096 * 17 = 69632 : 0 lost)
        return 1;
    else
        return 2;
}

void    *ft_malloc(size_t size) {
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

// void    ft_free(void *ptr) {
//     munmap(ptr, jsp wala);
// }
