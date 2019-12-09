/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:01:19 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 15:01:21 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# define FOLDER			4
# define LINK_TYPE		10
# define NONEXIST		-1
# define PERMISSION		0
# define DIR_EXIST		-2
# define BUFFSIZE       1500

/*
**		amounght of seconds in half of an year
*/
# define HULF_YEAR		15811200

char				g_recoursive_flag;
char				g_rev_flag;
char				g_t_flag;
char				g_l_flag;
char				g_a_flag;

short int			g_delim_links;
short int			g_delim_uid;
short int			g_delim_grid;
short int			g_delim_size;
short int           g_name_delimiter;

typedef struct		s_filenode
{
	char			*name;
	char			type_of_file;
	time_t			mod_time;
	int				access;
	char			*amounths_of_links;
	char			*username;
	char			*groupname;
	char			*size;
	int				extraaccess;
	char			*name_for_link;
	char            *fullname;
}					t_filenode;

typedef struct		s_dirnode
{
	char			*name;
	time_t			mod_time;
}					t_dirnode;

/*
**					add to libtf
*/
void				ft_twlstpush(t_twlist **beginlist, t_twlist *add);

/*
**					sort core
*/
void				sort(t_twlist **filenode);
int					sorting(t_twlist **begin,
									int(cmp(t_filenode *, t_filenode *)));
void				swap_list_filenodes(t_twlist *one, t_twlist *two);

/*
**					sort function
*/
int					cmp_filenode_name(t_filenode *one, t_filenode *two);
int					cmp_filenode_name_rev(t_filenode *one, t_filenode *two);
int					cmp_filenode_data(t_filenode *one, t_filenode *two);
int					cmp_filenode_data_rev(t_filenode *one, t_filenode *two);

/*
**					begining of programm
*/
int					start_the_programm(char *name, int num);
int					is_filename(char *name);

/*
**			 		flags
*/
int					recodnise_flag(char *flag_line);
void				nulg_l_flags(int	count);

/*
**			 		core
*/
int					simple_ls(char *name, t_twlist **dir_content,
															char *short_name);
int					recoursive_ls(t_twlist *all_files, char *name);
int					create_simplenode(int	type, char *name,
											char *full_name, t_filenode **new);
void				create_extrainf(char *name, struct stat box,
															t_filenode **info);
int					get_l_flag(t_filenode **new, char *full_name, int type);
/*
**					print
*/
void				put_names(t_twlist *lst, int total);
void				print_extra_info(t_twlist *lst);
void				print_type_and_access(t_filenode *file_info);
void				print_total(int	total);
void				print_with_spaces(int	c, int	len, char *str, char side);
void				print_link(char *name);
void				print_time(time_t mod_time);

/*
**			 		working with wrong dirname
*/
int					recodnise_dirname(char *name, int find);
int					flag_error(char *flag_or_filename);
void				print_nonexist(char *name);
void				print_exist(char *name, int type);
int					direrror(char *short_name, char *name,
														DIR *dir_fd, int find);
int					get_all_unexist(t_twlist *dirnames);

/*
**					clear
*/
void				clear_filenode(void *file, size_t size);
void				clear_filenode_name(void *file, size_t size);

/*
**					max_len
*/
void				fill_len_nuls(int	count);
void				count_max_len(t_filenode *inf);

#endif
