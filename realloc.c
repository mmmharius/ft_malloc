#include <libc.h>
#include <malloc.h>

void *realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return (malloc(size));
    if (size == 0) {
        free(ptr);
        return (NULL);
    }
    t_block *block = ((t_block *)ptr) - 1;
    if (size > block->size) {
        void *adr = malloc(size);
        void *ret = ft_memcpy(adr, ptr, block->size);
        free(ptr);
        return ret;
    }
    else if (size < block->size)
        split_block(block, size);
    return ptr;
    printf("test\n");
}
