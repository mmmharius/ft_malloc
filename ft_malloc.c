#include <libft.h>
#include <ft_malloc.h>
#include <sys/mman.h> //mmap

t_zone *create_zone(int type, size_t size) {

}

int    get_alloc_size(size_t size) {
    #if OS_TYPE == 1
        long page_size = sysconf(_SC_PAGESIZE);
    #elif OS_TYPE == 2
        long page_size = getpagesize(_SC_PAGESIZE);
    #else
    # warning "OS_TYPE not know ! use macOs/Linux pls"
        return 0;
    #endif
    if (size <= 90) // (90 + 32) * 100 = 12200 (88oct lost: 4096x3 = 12288);
        return 1;
    if (size <= 992) // (992 + 32 ) * 100 = 102400 (4096 * 25 = 102400 : 0 lost)
        return 2;
    else
        return 3;
}

void    *ft_malloc(size_t size) {
    t_zone  zone;
    t_block block;
    int type = get_alloc_size(size);
    zone = create_zone(type, size);
    printf("type:%d\n", type);
}
