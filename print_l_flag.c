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

#include "ft_ls.h"

void		print_link(char *name)
{
	ft_putstr(" -> ");
	if (name != NULL)
		ft_putstr(name);
}

void		print_with_spaces(int c, int len, char *str, char side)
{
	if (c < len)
		return ;
	if (side == 'r')
	{
		while (c >= len)
		{
			ft_putchar(' ');
			len++;
		}
	}
	ft_putstr(str);
	if (side == 'l')
	{
		while (c >= len)
		{
			ft_putchar(' ');
			len++;
		}
	}
}

void		print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

void		write_else(t_filenode *here)
{
	print_with_spaces(g_delim_links,
			ft_strlen(here->amounths_of_links), here->amounths_of_links, 'r');
	ft_putchar(' ');
	print_with_spaces(g_delim_uid,
			ft_strlen(here->username), here->username, 'l');
	ft_putchar(' ');
	print_with_spaces(g_delim_grid,
			ft_strlen(here->groupname), here->groupname, 'l');
	print_with_spaces(g_delim_size,
			ft_strlen(here->size), here->size, 'r');
	print_time(here->mod_time);
}

void		print_extra_info(t_twlist *lst)
{
	print_type_and_access(((t_filenode *)lst->content));
	write_else(((t_filenode *)lst->content));
}
