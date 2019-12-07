/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_recoursive_flag.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:46:40 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:46:42 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dir(char *dirname, t_twlist *dir, int total)
{
	ft_putstr("\n");
	ft_putstr(dirname);
	ft_putstr(":\n");
	put_names(dir, total);
}

int		get_next_dir(char *dirname, char *name)
{
	int			total;
	t_twlist	*all_files;
	t_twlist	*to_clear;

	if ((total = simple_ls(dirname, &all_files, name)) == -1)
		return (-1);
	print_dir(dirname, all_files, total);
	to_clear = all_files;
	all_files = to_clear;
	recoursive_ls(all_files, dirname);
	ft_twlstdel(&all_files, clear_filenode);
	return (0);
}

int		recoursive_ls(t_twlist *all_files, char *name)
{
	char		*path;
	char		*tmp;

	if (!(ft_strcmp(name, "/")))
		path = ft_strdup(name);
	else
		path = ft_strjoin(name, "/");
	while (all_files)
	{
		if (((t_filenode *)all_files->content)->type_of_file == FOLDER)
		{
			if ((ft_strcmp(((t_filenode *)all_files->content)->name, ".")
				&& ft_strcmp(((t_filenode *)all_files->content)->name, "..")))
			{
				tmp = ft_strjoin(path,
								((t_filenode *)all_files->content)->name);
				get_next_dir(tmp, ((t_filenode *)all_files->content)->name);
				ft_strdel(&tmp);
			}
		}
		all_files = all_files->next;
	}
	ft_strdel(&path);
	return (0);
}
