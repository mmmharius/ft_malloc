CC = cc
SRC = utils.c free.c malloc.c realloc.c show_alloc.c
MAIN = main.c
TEST_NAME = test
OBJS = $(SRC:.c=.o)

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
LINK = libft_malloc.so	

UNAME := $(shell uname -s)

ifeq ($(UNAME), Linux)
    OS_FLAG = -DOS_TYPE=1
endif

ifeq ($(UNAME), Darwin)
    OS_FLAG = -DOS_TYPE=2
endif

all: libc $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) ./libc/libc.a

%.o: %.c
	$(CC) $(OS_FLAG) -fPIC -I./libc -I. -c $< -o $@

test: libc $(MAIN) $(SRC)
	$(CC) $(OS_FLAG) -I. -I./libc $(MAIN) $(SRC) ./libc/libc.a -o $(TEST_NAME)

libc:
	make -C libc

clean:
	make -C libc clean
	rm -rf $(OBJS)

fclean:
	make -C libc fclean
	rm -rf $(OBJS) $(NAME) $(LINK) $(TEST_NAME)

re: clean all

.PHONY: all clean fclean re test libc