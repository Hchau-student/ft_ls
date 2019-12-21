/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:11 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:13 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		fill_len_nuls(int count)
{
	if (count != 5)
		return ;
	g_delim_links = 0;
	g_delim_uid = 0;
	g_delim_grid = 0;
	g_delim_size = 0;
	g_name_delimiter = 0;
}

void		count_max_len(t_filenode *inf)
{
	int		amounths_of_links;
	int		user_id;
	int		group_id;
	int		size;

	amounths_of_links = ft_strlen((inf)->amounths_of_links);
	user_id = ft_strlen((inf)->username);
	group_id = ft_strlen((inf)->groupname);
	size = ft_strlen((inf)->size);
	if (g_delim_links <= amounths_of_links)
		g_delim_links = amounths_of_links;
	if (g_delim_uid <= user_id)
		g_delim_uid = user_id;
	if (g_delim_grid <= group_id)
		g_delim_grid = group_id;
	if (g_delim_size <= size)
		g_delim_size = size;
}

void		compare_names(char *name)
{
	if ((size_t)g_name_delimiter < ft_strlen(name))
		g_name_delimiter = ft_strlen(name);
}
