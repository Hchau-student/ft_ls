/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:47:34 by hchau             #+#    #+#             */
/*   Updated: 2019/11/22 17:47:36 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_time(time_t mod_time)
{
	time_t		now;
	char		**time_res;
	int			i;

	time_res = NULL;
	i = 0;
	time_res = ft_strsplit(ctime(&(mod_time)), ' ');
	print_with_spaces(3, 3, time_res[1], 'r');
	print_with_spaces(2, ft_strlen(time_res[2]), time_res[2], 'r');
	ft_putchar(' ');
	if (time(&now) - mod_time > HULF_YEAR)
	{
		ft_putchar(' ');
		while ((ft_isdigit(time_res[4][i])))
			ft_putchar(time_res[4][i++]);
	}
	else
	{
		while ((time_res[3] + i) != (ft_strrchr(time_res[3], ':')))
			ft_putchar(time_res[3][i++]);
	}
	ft_freematr(time_res);
}
