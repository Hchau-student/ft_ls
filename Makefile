LS = ft_ls
CC = gcc -Wall -Wextra -Werror
SRC_DIR = srcs/
LIBFT_DIR = libft/
OBJ_DIR = obj/

LS_SRCS = main.c max_len.c print_access.c cleaning_up.c print_l_flag.c \
put_into_structs.c recuorsive_ls.c recodnise_flag.c simple_ls.c \
sort_functions.c sort.c start_the_programm.c print_err_arg.c if_direrror.c \
record_l_flag.c print_time.c

LS_OBJ = ${LS_SRCS:c=o}

all: $(LS)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I libft/ -I include/ -c -o $@ $^

$(LS): $(addprefix $(OBJ_DIR), $(LS_OBJ))
	@make -C $(LIBFT_DIR)
	@$(CC) $(addprefix $(OBJ_DIR), $(LS_OBJ)) $(LIBFT_DIR)libft.a -I libft/ -I include/ -o $(LS)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(LS)

re: fclean all