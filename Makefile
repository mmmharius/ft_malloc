NAME = ft_malloc
CC = cc
SRC = ft_malloc.c
MAIN = main.c
TEST_NAME = test
OBJS = $(SRC:.c=.o)
$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) -L./42_libft -lft

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    OS_FLAG = -DOS_TYPE=1
endif

ifeq ($(UNAME), Darwin)
    OS_FLAG = -DOS_TYPE=2
endif

$(TEST_NAME): $(MAIN) $(SRC)
	$(CC) $(OS_FLAG) -I. -I./42_libft $(MAIN) $(SRC) -L./42_libft -lft -o $(TEST_NAME)

all: libft $(NAME)
%.o: %.c
	$(CC) $(OS_FLAG) -fPIC -I./42_libft -I. -c $< -o $@	

libft:
	make -C 42_libft

clean:
	make -C 42_libft clean
	rm -rf $(OBJS)

fclean:
	make -C 42_libft fclean
	rm -rf $(OBJS) $(NAME) $(TEST_NAME)

re:	clean all

.PHONY:	all	clean fclean re test