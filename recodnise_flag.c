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
#include "../libft/libft.h"

int			recodnise_flag(char *flag_line)
{
	int		i;

	if (flag_line[0] && flag_line[0] != '-')
		return (-2);
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
	return (-3);
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
