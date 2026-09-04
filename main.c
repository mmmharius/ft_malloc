#include <malloc.h>
#include <libc.h>

int main() {
    struct t_block;

    void *tiny = malloc(1);
    malloc(1);
    malloc(55);
    malloc(1);
    malloc(1);
    malloc(1);
    malloc(1);
    malloc(1);
    malloc(1);
    malloc(1);
    void *small = malloc(1700);
    void *large = malloc(100);
    show_alloc_mem();
    free(tiny);
    free(small);
    free(large);
    free(NULL);
    return(0);
}