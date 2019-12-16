/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_R.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:01 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:03 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void				get_dir_time(t_twlist **dirname)
{
	t_twlist		*to_iter;
	struct stat		box;

	to_iter = *dirname;
	while (to_iter)
	{
		stat(((t_filenode *)to_iter->content)->name, &box);
		((t_filenode *)to_iter->content)->mod_time = box.st_mtime;
		to_iter = to_iter->next;
	}
}

void				sepparate_dirnames(int start, t_twlist **ghost_dirname,
										t_twlist **dirname, char **filenames)
{
	t_filenode	*inside;

	inside = NULL;
	while (filenames[start])
	{
		inside = (t_filenode *)malloc(sizeof(t_filenode));
		inside->name = ft_strdup(filenames[start]);
		if (((recodnise_dirname(inside->name, NONEXIST)) != DIR_EXIST))
			ft_twlstpush(&(*ghost_dirname),
					ft_twlstnew(inside, sizeof(t_filenode)));
		else
			ft_twlstpush(&(*dirname), ft_twlstnew(inside, sizeof(t_filenode)));
		start++;
		free(inside);
	}
}

t_twlist			*presort(int start, char **filenames)
{
	t_twlist	*dirname;
	t_twlist	*ghost_dirname;

	dirname = NULL;
	ghost_dirname = NULL;
	sepparate_dirnames(start, &ghost_dirname, &dirname, filenames);
	sorting(&ghost_dirname, cmp_filenode_name);
	if ((get_all_unexist(ghost_dirname)) == 1 && dirname != NULL)
		ft_putchar('\n');
	ft_twlstdel(&ghost_dirname, clear_filenode_name);
	if (g_t_flag == 1)
		get_dir_time(&dirname);
	sort(&dirname);
	return (dirname);
}

int					main(int ac, char **flag_or_filename)
{
	int				i;
	t_twlist		*sorted_folders;

	i = 1;
	nulg_l_flags(5);
	while (i <= ac && flag_or_filename[i]
			&& (recodnise_flag(flag_or_filename[i])) != -1)
		if ((flag_error(flag_or_filename[i++])))
			return (1);
	if (i == ac)
		return (start_the_programm(".", 0));
	else if (i + 1 == ac)
		return (start_the_programm(flag_or_filename[i], 0));
	if (!(sorted_folders = presort(i, flag_or_filename)))
		return (0);
	while (i <= ac && sorted_folders)
	{
		start_the_programm(((t_filenode *)sorted_folders->content)->name, i);
		if (!sorted_folders->next)
			break ;
		sorted_folders = sorted_folders->next;
		ft_putchar('\n');
	}
	ft_twlstdel_backw(&sorted_folders, clear_filenode_name);
	return (0);
}
