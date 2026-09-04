NAME = ft_malloc
CC = cc
SRC = ft_malloc.c
MAIN = main.c
TEST_NAME = test
OBJS = $(SRC:.c=.o)

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    OS_FLAG = -DOS_TYPE=1
endif

ifeq ($(UNAME), Darwin)
    OS_FLAG = -DOS_TYPE=2
endif

all: libc $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) -L./libc

%.o: %.c
	$(CC) $(OS_FLAG) -fPIC -I./libc -I. -c $< -o $@

test: libc $(MAIN) $(SRC)
	$(CC) $(OS_FLAG) -I. -I./libc $(MAIN) $(SRC) -L./libc -lft -o $(TEST_NAME)

libc:
	make -C libc

clean:
	make -C libc clean
	rm -rf $(OBJS)

fclean:
	make -C libc fclean
	rm -rf $(OBJS) $(NAME) $(TEST_NAME)

re: clean all

.PHONY: all clean fclean re test libc