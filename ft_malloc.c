#include <libft.h>
#include <ft_malloc.h>

// typedef struct s_malloc_data {
//     t_zone *zones[3]; // zones[0] = tiny, zones[1] = small, zones[2] = large
// } t_malloc_data;

t_malloc_data g_malloc = {{NULL, NULL, NULL}};

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
    // printf("%d | %zu\n", zone->type, zone->size);
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
    t_zone *zone = create_zone(type, size);
    if (zone == NULL)
        return (perror("mmap:"), NULL); 
    return (zone->blocks + 1);
}

// void    ft_free(void *ptr) {
//     munmap(ptr, jsp wala);
// }
