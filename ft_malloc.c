#include <libft.h>
#include <ft_malloc.h>
#include <sys/mman.h> //mmap

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
    if (type == 1) {
        ptr = mmap(NULL, 12288, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        size = 12288;
    }
    else if (type == 2) {
        ptr = mmap(NULL, 69632, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        size = 69632;
    }
    else {
        size_t nbr_page = ((size + sizeof(t_zone) + sizeof(t_block)) + page_size - 1) / page_size;
        size_t size_mmap = nbr_page * page_size;
        // printf("nbr_page: %zu, size : %zu\n", nbr_page, size);
        ptr = mmap(NULL, size_mmap, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        ptr = NULL;
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
    // printf("%d | %zu\n", zone->type, zone->size);
    return (zone);
}

int    get_alloc_size(size_t size) {

    if (size <= 90) // 32 + ( (90 + 32) * 100 ) = 12232 (56oct lost: 4096x3 = 12288);
        return 1;
    if (size <= 664) // 32 + ( (664 + 32 ) * 100 ) = 69632 (4096 * 17 = 69632 : 0 lost)
        return 2;
    else
        return 3;
}

void    *ft_malloc(size_t size) {
    t_block block;
    int type = get_alloc_size(size);
    t_zone *zone = create_zone(type, size);
    printf(zone)
    if (zone == NULL)
        return (perror("mmap:"), NULL); 
    return (zone->blocks);
}

void    ft_free(void *ptr) {
    munmap(ptr, jsp wala);
}
