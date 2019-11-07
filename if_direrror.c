/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_direrror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:02:09 by hchau             #+#    #+#             */
/*   Updated: 2019/11/06 14:02:11 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			is_filename(char *name)
{
	DIR				*to_open;

	if (!(to_open = opendir(name)))
		return (-1);
	if (closedir(to_open) == -1)
		ft_putstr("closedir error");
	return (0);
}

int			direrror(char *short_name, char *name, DIR *dir_fd, int find)
{
	struct dirent		*reading;

	while ((reading = readdir(dir_fd)))
	{
		if (!(ft_strcmp(reading->d_name, short_name)))
		{
			if (find == NONEXIST)
			{
				if (reading->d_type != FOLDER)
					return (reading->d_type);
				return (DIR_EXIST);
			}
			print_exist(name, reading->d_type);
			return (PERMISSION);
		}
	}
	if (find == NONEXIST)
		return (NONEXIST);
	print_nonexist(name);
	return (NONEXIST);
}

int			recodnise_dirname(char *name, int find)
{
	char	*short_name;
	char	*dirname;
	DIR		*dir_fd;
	int		res;

	if ((is_filename(name)) != -1)
		return (DIR_EXIST);
	if (ft_strrchr(name, '/'))
		short_name = ft_strdup(ft_strrchr(name, '/') + 1);
	else
		short_name = ft_strdup(name);
	dirname = ft_strdup(name);
	if ((ft_strrchr(dirname, '/')) != NULL)
		ft_strrchr(dirname, '/')[0] = '\0';
	if (!(dir_fd = opendir(dirname)))
		dir_fd = opendir(".");
	res = direrror(short_name, name, dir_fd, find);
	closedir(dir_fd);
	ft_strdel(&short_name);
	ft_strdel(&dirname);
	return (res);
}

int			get_all_unexist(t_twlist *dirnames)
{
	int			res;
	int			flag;
	t_twlist	*to_iter;

	to_iter = dirnames;
	flag = 0;
	while (dirnames)
	{
		if ((recodnise_dirname(((t_filenode *)dirnames->content)->name,
								NONEXIST)) == NONEXIST)
			print_nonexist(((t_filenode *)dirnames->content)->name);
		dirnames = dirnames->next;
	}
	while (to_iter)
	{
		if ((res = recodnise_dirname(((t_filenode *)to_iter->content)->name,
								NONEXIST)) != NONEXIST)
		{
			print_exist(((t_filenode *)to_iter->content)->name, res);
			flag = 1;
		}
		to_iter = to_iter->next;
	}
	return (flag);
}
