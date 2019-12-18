/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colored_multicolomns.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 15:58:29 by hchau             #+#    #+#             */
/*   Updated: 2019/12/17 15:58:35 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			count_str(char *buf)
{
	int		count;

	count = 0;
	while (*buf)
	{
		if (*buf == '\n')
			count++;
		buf++;
	}
	return (count);
}

t_twlist	*get_next(t_twlist *lst, int str)
{
	while (str > 0)
	{
		if (!(lst = lst->next))
			return (NULL);
		str--;
	}
	return (lst);
}

int			get_multicolomn_colored_str(t_twlist *lst, int strs)
{
	char		*iter;
	char		buf[10000];
	int			count_change;

	count_change = 0;
	iter = (char *)buf;
	while (lst)
	{
		iter = get_coloured_name(&iter, ((t_filenode *)lst->content));
		count_change += g_name_delimiter -
				ft_strlen(((t_filenode *)lst->content)->name);
		while (count_change)
		{
			*iter = ' ';
			iter++;
			count_change--;
		}
		*iter = '\0';
		ft_putstr(buf);
		iter = (char *)buf;
		lst = get_next(lst, strs);
	}
	*iter = '\0';
	return (0);
}

void		put_colored_multicolomns(char **buf, t_twlist *lst)
{
	int		strs;
	int		counter;

	strs = count_str(*buf);
	counter = strs;
	while (counter)
	{
		get_multicolomn_colored_str(lst, strs);
		lst = lst->next;
		counter--;
		ft_putchar('\n');
	}
	ft_strdel(buf);
}
