/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:01:19 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 20:12:31 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>

/*
**		type defines
*/
# define FOLDER				4
# define LINK_TYPE			10

/*
**		direrror defines
*/
# define NONEXIST			-1
# define PERMISSION			0
# define DIR_EXIST			-2

/*
**		color defines
*/
# define DIR_CLR			"\033[34m"
# define DIR_ACCESS_CLR		"\033[43m\033[30m"
# define END_OF_CLR			"\033[0m"
# define LINK_CLR			"\033[35m"
# define REG_ACCESS_CLR		"\033[31m"
# define ST_BIT_CLR			"\033[42m\033[30m"
# define BLACK_TXT_CLR		"\033[30m"

/*
**		pride colors defines
*/
# define RED_START			0x00FF0000
# define RED_STOP			0x00FF00FF
# define ORANGE_START		0x00FA7F00
# define ORANGE_STOP		0x00FA7FFF
# define YELLOW_START		0x00ECE200
# define YELLOW_STOP		0x00ECE2FF
# define GREEN_START		0x003CA500
# define GREEN_STOP			0x003CA5FF
# define BLUE_START			0x000080F0
# define BLUE_STOP			0x000080FF
# define PURPLE_START		0x00C808F0
# define PURPLE_STOP		0x00C808FF

/*
**		amounght of seconds in half of an year
*/
# define HULF_YEAR		15711200

/*
**		buff work
*/
# define BUFFSIZE       	4000

int							g_print_count;
char						g_buf[BUFFSIZE];
/*
**		flag globals
*/
char						g_recoursive_flag;
char						g_rev_flag;
char						g_t_flag;
char						g_l_flag;
char						g_a_flag;
char						g_f_flag;
char						g_colour_flag;
char						g_g_flag;
char						g_d_flag;
char						g_u_flag;
char						g_multicolomn_flag;
/*
**		Александр
*/
char						g_gay_flag;
char						g_unset_flag;
/*
**		delimiter globals
*/
short int					g_delim_links;
short int					g_delim_uid;
short int					g_delim_grid;
short int					g_delim_size;
short int					g_name_delimiter;

typedef struct				s_datalist
{
	int						content;
	struct s_datalist		*next;
}							t_datalist;

typedef struct				s_filenode
{
	char					*name;
	char					*fullname;
	char					type_of_file;
	time_t					mod_time;
	int						access;
	char					*amounths_of_links;
	char					*username;
	char					*groupname;
	char					*size;
	int						extraaccess;
	char					*name_for_link;
}							t_filenode;

/*
**					add to libtf
*/
void						ft_twlstpush(t_twlist **beginlist, t_twlist *add);
void						ft_twlstpush_line(t_twlist **beginlist,
							t_twlist *add);
void						ft_lstpush(t_list **beginlist, t_list *add);
/*
**					sort core
*/
void						sort(t_twlist **filenode);
int							sorting(t_twlist **begin,
									int(cmp(t_filenode *, t_filenode *)));
void						swap_list_filenodes(t_twlist *one, t_twlist *two);
void						func_presort(t_twlist **lst, int index);
void						range_int_rev(t_list **all);
void						range_int(t_list **all);
int							get_index(char *name, int i);
int							get_presort_index(int i, t_list **all_i,
								t_twlist **presort, t_twlist *put);
t_list						*get_next_lst(t_list **cur);
void						get_abc_result(t_twlist *presort[251],
							t_list *all_i, t_twlist **dir_content);
/*
**					sort function
*/
int							cmp_filenode_name(t_filenode *one, t_filenode *two);
int							cmp_filenode_name_rev(t_filenode *one,
							t_filenode *two);
int							cmp_filenode_data(t_filenode *one, t_filenode *two);
int							cmp_filenode_data_rev(t_filenode *one,
							t_filenode *two);
void						get_no_sort(t_twlist **dir_content);

/*
**					begining of programm
*/
int							start_the_programm(char *name, int num);
int							is_filename(char *name);

/*
**			 		flags
*/
int							recodnise_flag(char *flag_line);
void						nulg_l_flags(int count);

/*
**			 		core
*/
int							simple_ls(char *name, t_twlist **dir_content,
															char *short_name);
int							recoursive_ls(t_twlist *all_files, char *name);
int							create_simplenode(int	type, char *name,
											char *full_name, t_filenode **new);
void						create_extrainf(char *name, struct stat box,
															t_filenode **info);
int							get_l_flag(t_filenode **new, char *full_name,
							int type);
/*
**					little helpers
*/
char						*get_name(char *name);
void						write_full_buf(char **to_iter);
/*
**					print
*/
void						put_names(t_twlist *lst, int total);
char						*print_extra_info(t_twlist *lst, char **buf);
char						*print_type_and_access(t_filenode *file_info,
							char **buf);
void						print_total(int	total);
char						*print_with_spaces(int	c,
							char **buf, char *str, char side);
char						*print_link(char *name, char **buf);
char						*print_time(time_t mod_time, char **buf);
void						write_full_buf(char **to_iter);
char						*get_coloured_name(char **str, t_filenode *src);
void						put_gay_str(int color);
char						*check_pride_russia(char *check);
int							get_terminal_vertical(void);
int							recodnise_rus_color(char color, int *stop, int len);
/*
**					multicolomns
*/
void						print_multicolomn(t_twlist *lst);
int							get_terminal_props(void);
int							get_correct_space(int term_size);
int							count_all_names(t_twlist *lst);
int							correct_coloumns(int names, int *coloumns, int len);
void						put_colored_multicolomns(char **buf, t_twlist *lst);

/*
**			 		working with wrong dirname
*/
int							recodnise_dirname(char *name, int find);
int							flag_error(char *flag_or_filename);
void						print_nonexist(char *name);
void						print_exist(char *name, int type);
int							direrror(char *short_name, char *name,
														DIR *dir_fd, int find);
int							get_all_unexist(t_twlist *dirnames);

/*
**					clear
*/
void						clear_filenode(void *file, size_t size);
void						clear_filenode_name(void *file, size_t size);
void						clear_lst_nbr(void *file, size_t size);

/*
**					max_len
*/
void						fill_len_nuls(int	count);
void						count_max_len(t_filenode *inf);
void						compare_names(char *name);

#endif
