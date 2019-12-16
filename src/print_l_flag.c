/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_g_l_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:34 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 17:57:45 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*print_link(char *name, char **buf)
{
	char	*iter;

	iter = *buf;
	iter = ft_strcpy_return(iter, " -> ");
	g_print_count += 4;
	if (name != NULL)
	{
		iter = ft_strcpy_return(iter, name);
		g_print_count += ft_strlen(name);
	}
	return (iter);
}

char	*print_with_spaces(int c, char **buf, char *str, char side)
{
	int		len;
	char	*iter;

	iter = *buf;
	if ((len = ft_strlen(str)) > c)
		return (iter);
	if (side == 'r')
	{
		while (c + 1 >= ++len)
		{
			*(iter++) = ' ';
			g_print_count++;
		}
	}
	iter = ft_strcpy_return(iter, str);
	g_print_count += ft_strlen(str);
	if (side == 'l')
	{
		while (c + 1 >= ++len)
		{
			*(iter++) = ' ';
			g_print_count++;
		}
	}
	return (iter);
}

void	print_total(int total)
{
	ft_putstr("total ");
	ft_putnbr(total);
	ft_putchar('\n');
}

char	*write_else(t_filenode *here, char **buf)
{
	char	*iter;

	iter = *buf;
	iter = print_with_spaces(g_delim_links,
			&iter, here->amounths_of_links, 'r');
	g_print_count += 1;
	*(iter++) = ' ';
	if (!g_g_flag)
	{
		iter = print_with_spaces(g_delim_uid,
								&iter, here->username, 'l');
		*(iter++) = ' ';
		g_print_count += 1;
	}
	iter = print_with_spaces(g_delim_grid,
					&iter, here->groupname, 'l');
	iter = print_with_spaces(g_delim_size,
					&iter, here->size, 'r');
	iter = print_time(here->mod_time, &iter);
	return (iter);
}

char	*print_extra_info(t_twlist *lst, char **buf)
{
	char	*iter;

	iter = *buf;
	if (g_print_count >= 2500)
		write_full_buf(&iter);
	iter = print_type_and_access(((t_filenode *)lst->content), &iter);
	if (g_print_count >= 2500)
		write_full_buf(&iter);
	iter = write_else(((t_filenode *)lst->content), &iter);
	if (g_print_count >= 2500)
		write_full_buf(&iter);
	return (iter);
}
