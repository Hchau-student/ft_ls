/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recodnise_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:53 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:54 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			flag_error(char *flag_or_filename)
{
	int		if_flag;

	if_flag = recodnise_flag(flag_or_filename);
	if (flag_or_filename && if_flag != -2)
	{
		if ((is_filename(flag_or_filename)) == -1)
		{
			write(1, "illegal option -- ", 18);
			ft_putchar(flag_or_filename[if_flag]);
			write(1, "\n", 1);
			write(1, "usage: ft_ls [-Ralrt] [file ...]\n", 33);
			return (1);
		}
	}
	return (0);
}

int			recodnise_flag(char *flag_line)
{
	int		i;

	if ((flag_line[0] && flag_line[0] != '-') ||
		(flag_line[0] && !(flag_line[1])))
		return (-1);
	i = 1;
	while (flag_line[i])
	{
		if (flag_line[i] == 'R')
			g_recoursive_flag = 1;
		else if (flag_line[i] == 'r')
			g_rev_flag = 1;
		else if (flag_line[i] == 'a')
			g_a_flag = 1;
		else if (flag_line[i] == 't')
			g_t_flag = 1;
		else if (flag_line[i] == 'l')
			g_l_flag = 1;
		else if (flag_line[i] == '1')
			;
		else
			return (i);
		i++;
	}
	return (-2);
}

void		nulg_l_flags(int count)
{
	if (count == 5)
	{
		g_recoursive_flag = 0;
		g_rev_flag = 0;
		g_t_flag = 0;
		g_l_flag = 0;
		g_a_flag = 0;
	}
}
