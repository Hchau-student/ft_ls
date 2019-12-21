/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_and_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 18:06:45 by hchau             #+#    #+#             */
/*   Updated: 2019/12/20 18:06:47 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char		*music(char *to_return)
{
	if (g_unset_flag)
	{
		system("pkill afplay");
		exit(0);
	}
	if (g_gay_flag)
		system("afplay ./src/Take_on_Me.mp3 &");
	return (to_return);
}

char		*check_unset(char *check)
{
	char	unset_src[20];
	char	*iter;

	ft_strcpy(unset_src, "unset_music_");
	iter = unset_src;
	while (*check && *check == *iter)
	{
		check++;
		iter++;
	}
	if (!*iter)
	{
		g_unset_flag = 1;
		return (music("_unset_music_"));
	}
	*iter = '\0';
	return (NULL);
}

char		*check_pride_russia(char *check)
{
	char	pride_src[15];
	char	*iter;

	ft_strcpy(pride_src, "_set_pride_");
	iter = pride_src;
	while (*check && *check == *iter)
	{
		check++;
		iter++;
	}
	if (!*iter)
	{
		g_gay_flag = 1;
		return (music("_set_pride_"));
	}
	if (*check == 'u')
		return (check_unset(check));
	*iter = '\0';
	return (NULL);
}
