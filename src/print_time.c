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

#include "../inc/ft_ls.h"

char		*get_minutes(char **put, char *copy, char flag)
{
	int		i;
	char	*iter;

	iter = *put;
	i = 0;
	if (flag == 'y')
	{
		*(iter++) = ' ';
		g_print_count++;
	}
	while (copy[i] && copy[i] != '\n')
	{
		*(iter++) = copy[i++];
		g_print_count++;
	}
	return (iter);
}

char		*print_time(time_t mod_time, char **buf)
{
	time_t		now;
	char		**time_res;
	char		*iter;

	iter = *buf;
	time_res = NULL;
	time_res = ft_strsplit(ctime(&(mod_time)), ' ');
	iter = print_with_spaces(3, &iter, time_res[1], 'r');
	iter = print_with_spaces(2, &iter, time_res[2], 'r');
	*(iter++) = ' ';
	g_print_count++;
	if (time(&now) - mod_time > HULF_YEAR)
		iter = get_minutes(&iter, time_res[4], 'y');
	else
	{
		*(ft_strrchr(time_res[3], ':')) = '\0';
		iter = get_minutes(&iter, time_res[3], 0);
	}
	ft_freematr(time_res);
	*(iter++) = ' ';
	g_print_count++;
	return (iter);
}
