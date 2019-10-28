/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_g_l_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:34 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:35 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdio.h>
#include "../libft/libft.h"

void		print_link(char *name)
{
	ft_putstr(" -> ");
	if (name != NULL)
		ft_putstr(name);
}

void		print_with_spaces(int c, int len, char *str)
{
	if (c < len)
		return ;
	if (c < 0)
		return ;
	while (c >= len)
	{
		ft_putchar(' ');
		len++;
	}
	ft_putstr(str);
}

void		print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void		write_else(t_filenode *here)
{
	char	**time_res;
	int		i;

	print_with_spaces(g_delim_links,
			ft_strlen(here->amounths_of_links), here->amounths_of_links);
	print_with_spaces(g_delim_uid,
			ft_strlen(here->username), here->username);
	print_with_spaces(g_delim_grid + 1,
			ft_strlen(here->groupname), here->groupname);
	print_with_spaces(g_delim_size + 1,
			ft_strlen(here->size), here->size);
	time_res = ft_strsplit(ctime(&(here->mod_time_sec)), ' ');
	print_with_spaces(3, 3, time_res[1]);
	print_with_spaces(2, ft_strlen(time_res[2]), time_res[2]);
	i = 0;
	ft_putchar(' ');
	while ((time_res[3] + i) != (ft_strrchr(time_res[3], ':')))
		ft_putchar(time_res[3][i++]);
	ft_freematr(time_res);
}

void		print_extra_info(t_twlist *lst)
{
	print_type_and_access(((t_filenode *)lst->content));
	write_else(((t_filenode *)lst->content));
}
