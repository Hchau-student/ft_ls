LS = ft_ls
CC = gcc -Wall -Wextra -Werror
SRC_DIR = src/
LIBFT_DIR = libft/
OBJ_DIR = obj/

LS_SRCS = main.c max_len.c print_access.c cleaning_up.c print_l_flag.c \
		put_into_structs.c recuorsive_ls.c recodnise_flag.c simple_ls.c \
		sort_functions.c sort.c start_the_programm.c print_err_arg.c if_direrror.c \
		record_l_flag.c print_time.c presort.c get_index.c little_helpers.c color.c \
		multicolomn.c count_multicolomns.c colored_multicolomns.c put_rainbow_str.c \
		music_and_color.c \

LS_OBJ = ${LS_SRCS:c=o}

all: $(LS)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -I libft/ -I ./ -c -o $@ $^

$(LS): $(addprefix $(OBJ_DIR), $(LS_OBJ))
	@make -C $(LIBFT_DIR)
	@$(CC) $(addprefix $(OBJ_DIR), $(LS_OBJ)) $(LIBFT_DIR)libft.a -I libft/ -I inc/ -o $(LS)
	@echo "\033[38;2;139;20;39m A \033[38;2;190;60;0m L \033[38;2;255;156;0m L \
	\033[38;2;252;210;0m   D \033[38;2;60;160;50m O \033[38;2;32;80;250m N \033[38;2;200;8;250m E \033[0m"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[38;2;139;20;39m A \033[38;2;190;60;0m L \033[38;2;255;156;0m L \
	\033[38;2;252;210;0m   C \033[38;2;60;160;50m L \033[36m E \033[38;2;32;80;250m A \033[38;2;200;8;250m N \033[0m"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(LS)

re: fclean all