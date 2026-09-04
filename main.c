#include <ft_malloc.h>

int main() {
    struct t_block;

    void *tiny = ft_malloc(1);
    void *small = ft_malloc(700);
    void *large = ft_malloc(100000);
    ft_free(tiny);
    ft_free(small);
    ft_free(large);
    ft_free(NULL);
    return(0);
}