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
	int		i;
	int		j;
	t_zone	*tmp;

	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			if (arr[j] < arr[i])
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	show_alloc_mem(void)
{
	t_zone	*arr[128];
	t_zone	*z;
	t_block	*block;
	size_t	total;
	int		n;
	int		i;
	char	*labels[3] = {"TINY", "SMALL", "LARGE"};
	int		type;

	total = 0;
	type = 0;
	while (type < 3)
	{
		n = count_zones(g_malloc.zones[type]);
		i = 0;
		z = g_malloc.zones[type];
		while (z)
		{
			arr[i++] = z;
			z = z->next;
		}
		sort_adr(arr, n);
		i = 0;
		while (i < n)
		{
			ft_printf("%s : %p\n", labels[type], (void *)arr[i]);
			block = arr[i]->blocks;
			while (block)
			{
				if (!block->free)
				{
					ft_printf("%p - %p :", (void *)(block + 1), (void *)((char *)(block + 1) + block->size));
                    ft_putnbr_fd((int)block->size, 1);
                    write(1, " bytes\n", 7);
					total += block->size;
				}
				block = block->next;
			}
			i++;
		}
		type++;
	}
    ft_printf("Total :"); 
    ft_putnbr_fd((int)total, 1);
	ft_printf(" bytes\n");
}