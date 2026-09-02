#include <ft_malloc.h>

int main() {
    struct t_block;

    void *ptr = ft_malloc(1);
    printf("ptr = %p\n", ptr);
    char *data = (char*  )ptr;
    data[0] = 'A';
    printf("data = %c\n", data[0]);
    t_block *blocks = ((t_block *)ptr) - 1;
    printf("size=%zu, free=%d\n", blocks->size, blocks->free);
    printf("tiny zone ptr = %p\n", (void *)g_malloc.zones[0]); 
    ft_malloc(1);
    printf("tiny zone ptr = %p\n", (void *)g_malloc.zones[0]);
    ft_malloc(100000);
    return(0);
}