NAME = malloc
CC = cc
SRC = malloc.c
OBJS = $(SRC:.c=.o)
$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) -L./42_libft -lft

all: libft $(NAME)
%.o: %.c
	$(CC) -fPIC -I./42_libft -c $< -o $@	

libft:
	make -C 42_libft

clean:
	make -C 42_libft clean
	rm -rf $(OBJS)

fclean:
	make -C 42_libft fclean
	rm -rf $(OBJS) $(NAME)

re:	clean all
	
.PHONY:	all	clean fclean re