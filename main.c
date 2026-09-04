#include <malloc.h>
#include <libc.h>

int main(void)
{
    void *t1 = malloc(1);
    void *t2 = malloc(42);
    void *t3 = malloc(90);
    void *s1 = malloc(91);
    void *s2 = malloc(300);
    void *s3 = malloc(664);
    void *l1 = malloc(665);
    void *l2 = malloc(4096);

    show_alloc_mem();

    t2 = realloc(t2, 80);
    s2 = realloc(s2, 100);
    void *r1 = realloc(NULL, 50);
    (void)realloc(l2, 0);

    show_alloc_mem();

    free(t1);
    free(t3);
    free(s1);
    free(s3);
    free(l1);
    free(t2);
    free(s2);
    free(r1);

    free(NULL);

    show_alloc_mem();

    return (0);
}