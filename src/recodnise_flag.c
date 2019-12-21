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

#include "../inc/ft_ls.h"

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
			ft_putstr("usage: ft_ls "
			"[-GRadfglrtu]"
			"[_set_pride_]"
			"[_unset_music_]"
			" [file ...]\n");
			return (1);
		}
	}
	return (0);
}

int			is_flag(char check)
{
	if (check == 'R')
		g_recoursive_flag = 1;
	else if (check == 'r')
		g_rev_flag = 1;
	else if (check == 'a')
		g_a_flag = 1;
	else if (check == 't')
		g_t_flag = 1;
	else if (check == 'l')
		g_l_flag = 1;
	else if (check == 'G')
		g_colour_flag = 1;
	else if (check == 'f')
		g_f_flag = 1;
	else if (check == 'g')
		g_g_flag = 1;
	else if (check == 'd')
		g_d_flag = 1;
	else if (check == 'u')
		g_u_flag = 1;
	else if (check == '1')
		g_multicolomn_flag = 0;
	else
		return (-1);
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
		if ((is_flag(flag_line[i])) != -1)
			i++;
		else if (flag_line[i] == '_')
		{
			if (!(check_pride_russia(flag_line + i)))
				return (i);
			i += ft_strlen(check_pride_russia(flag_line + i));
		}
		else
			return (i);
	}
	if (g_colour_flag && g_gay_flag)
		g_gay_flag = 0;
	if ((g_l_flag || g_g_flag) && g_multicolomn_flag)
		g_multicolomn_flag = 0;
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
		g_colour_flag = 0;
		g_f_flag = 0;
		g_g_flag = 0;
		g_d_flag = 0;
		g_u_flag = 0;
		g_gay_flag = 0;
		g_multicolomn_flag = 1;
		g_unset_flag = 0;
	}
}
