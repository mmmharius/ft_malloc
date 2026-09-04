#include <libc.h>
#include <malloc.h>

static int	count_zones(t_zone *z)
{
    int n;
    for (n = 0; z; z = z->next, n++)
        ;
    return n;
}

static void	sort_adr(t_zone **arr, int n)
{
	t_zone	*tmp;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
        }
    }
}

void	show_alloc_mem(void)
{
	t_zone	*arr[128];
	t_zone	*z;
	t_block	*block;
	size_t	total = 0;
	int		n, i;
	char	*labels[3] = {"TINY", "SMALL", "LARGE"};

    for (int type = 0; type < 3; type++) {
        n = count_zones(g_malloc.zones[type]);
        i = 0;
        for (z = g_malloc.zones[type]; z != NULL; z = z->next, i++)
            arr[i] = z;
        sort_adr(arr, n);
        for (i = 0; i < n; i++) {
            ft_printf("%s : %p\n", labels[type], (void *)arr[i]);
            for (block = arr[i]->blocks; block != NULL; block = block->next) {
                if (!block->free)
				{
					ft_printf("%p - %p :", (void *)(block + 1), (void *)((char *)(block + 1) + block->size));
                    ft_putnbr_fd((int)block->size, 1);
                    write(1, " bytes\n", 7);
					total += block->size;
				}
            }
        }
    }
    ft_printf("Total :"); 
    ft_putnbr_fd((int)total, 1);
	ft_printf(" bytes\n");
}