CC = gcc
LIB_DIR = libft/
FLAGS = -Wall -Werror -Wextra
LIB_NAME = libft.a
SRCS = srcs/main.c srcs/max_len.c srcs/print_access.c srcs/cleaning_up.c \
srcs/print_l_flag.c srcs/put_into_structs.c srcs/recuorsive_ls.c srcs/recodnise_flag.c srcs/simple_ls.c \
srcs/sort_functions.c srcs/sort.c srcs/start_the_programm.c
INCS = libft/
OBJ = main.o max_len.o print_access.o cleaning_up.o \
print_l_flag.o put_into_structs.o recuorsive_ls.o recodnise_flag.o simple_ls.o \
sort_functions.o sort.o start_the_programm.o
NAME = ft_ls

all: $(LIB_NAME) $(NAME)

$(LIB_NAME):
	make -C $(LIB_DIR) $(LIB_NAME)

$(NAME): $(LIB_NAME)
	$(CC) -c $(SRCS) -I $(INCS) $(FLAGS)
	$(CC) $(OBJ) -o $(NAME) -L $(LIB_DIR) -lft
	rm -Rf $(INCS)*.h.gch
clean:
	make -C $(LIB_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIB_DIR) fclean
	rm -f $(NAME)

re: fclean all

rclean: re clean