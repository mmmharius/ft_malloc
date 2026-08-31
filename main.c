#include <ft_malloc.h>

int main() {
    // int lenght = 6;
    // void *zone = mmap(NULL, lenght, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    // if (zone == MAP_FAILED)
    //     return(perror("mmap:"), -1);
    // char hello[6] = "hello\n";
    // ft_memcpy(zone, hello, 6);
    // char *str = (char *)zone;
    // for (int i = 0; str[i]; i++)
    //     printf("%c", str[i]);
    // munmap(zone, lenght);
    ft_malloc(1);
    return(0);
}