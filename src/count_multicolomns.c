/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_multicolomns.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 00:53:17 by hchau             #+#    #+#             */
/*   Updated: 2019/12/17 00:53:23 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			get_terminal_props(void)
{
	struct winsize	ws;
	int				num_col;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	num_col = ws.ws_col;
	return (num_col);
}

int			get_correct_space(int term_size)
{
	int		count_colomn;

	if (g_name_delimiter >= term_size)
	{
		count_colomn = 1;
		return (count_colomn);
	}
	if (g_colour_flag)
		while (g_name_delimiter % 9)
			g_name_delimiter++;
	else
		while (g_name_delimiter % 8)
			g_name_delimiter++;
	count_colomn = term_size / (g_name_delimiter);
	return (count_colomn);
}

int			count_all_names(t_twlist *lst)
{
	int		count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

int			correct_coloumns(int names, int *coloumns, int len)
{
	int		how_much;

	how_much = 0;
	if (len <= g_name_delimiter)
		return (0);
	if (names <= *coloumns)
	{
		*coloumns = names;
		return (0);
	}
	while (names > *coloumns)
	{
		how_much++;
		names -= *coloumns;
	}
	if (how_much == 0)
		return (1);
	return (0);
}
