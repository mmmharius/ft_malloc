#include <libft.h>
#include <ft_malloc.h>
#include <sys/mman.h> //mmap

void    get_alloc_size(size_t size) {
    #if OS_TYPE == 1
        long page_size = sysconf(_SC_PAGESIZE);
    #elif OS_TYPE == 2
        long page_size = getpagesize(_SC_PAGESIZE);
    #else
    # warning "OS_TYPE not know ! use macOs/Linux pls"
    #endif
    printf("page_size:%ld\n", page_size);
}

void    *ft_malloc(size_t size) {
    get_alloc_size(size);
    return 0;
}
