/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_programm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:29 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:48:30 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		put_names(t_twlist *lst, int total)
{
	if (!lst || !lst->content)
		return ;
	if (g_l_flag == 1)
		print_total(total);
	while (lst)
	{
		if (g_l_flag == 1 && total != -2)
		{
			print_extra_info(lst);
			ft_putchar(' ');
		}
		ft_putstr(((t_filenode *)lst->content)->name);
		if (g_l_flag == 1 && total != -2)
		{
			if (((t_filenode *)lst->content)->type_of_file == 10)
				print_link(((t_filenode *)lst->content)->name_for_link);
		}
		ft_putchar('\n');
		lst = lst->next;
	}
}

int			start_the_programm(char *filename, int num)
{
	t_twlist		*first_look;
	int				total;

	if (num != 0)
	{
		ft_putstr(filename);
		ft_putstr(":\n");
	}
	if (recodnise_dirname(filename, DIR_EXIST) != DIR_EXIST)
		return (0);
	if ((total = simple_ls(filename, &first_look, filename)) == -1)
		return (0);
	put_names(first_look, total);
	if (g_recoursive_flag == 1)
		if ((recoursive_ls(first_look, filename)) == -1)
			ft_putendl("Error read");
	if (first_look != NULL)
		ft_twlstdel(&first_look, clear_filenode);
	return (0);
}
