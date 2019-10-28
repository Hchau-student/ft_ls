/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:11 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:48:13 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort(t_twlist **filenode)
{
	if (!filenode || !*filenode)
		return ;
	if (!g_rev_flag && !g_t_flag)
		sorting(filenode, cmp_filenode_name);
	if (g_rev_flag && !g_t_flag)
		sorting(filenode, cmp_filenode_name_rev);
	if (!g_rev_flag && g_t_flag)
	{
		sorting(filenode, cmp_filenode_data);
	}
	if (g_rev_flag && g_t_flag)
	{
		sorting(filenode, cmp_filenode_data_rev);
	}
}

void		swap_list_filenodes(t_twlist *one, t_twlist *two)
{
	t_filenode		*tmp;

	tmp = ((t_filenode *)one->content);
	one->content = two->content;
	two->content = tmp;
}

void		get_min(t_twlist **begin, t_twlist **val, t_twlist **val_save,
					int (cmp(t_filenode *, t_filenode *)))
{
	{
		while (*begin && (*begin)->prev && (*begin)->prev != *val_save)
		{
			if (cmp((*begin)->content, (*val)->content) < 0)
				*val = *begin;
			*begin = (*begin)->prev;
		}
	}
	swap_list_filenodes((*begin), (*val));
	*val_save = (*begin);
	*val = (*begin)->next;
}

void		get_max(t_twlist **begin, t_twlist **val, t_twlist **val_save,
									int (cmp(t_filenode *, t_filenode *)))
{
	{
		while (*begin && (*begin)->next && (*begin)->next != *val_save)
		{
			if (cmp((*begin)->content, (*val)->content) > 0)
				*val = *begin;
			*begin = (*begin)->next;
		}
	}
	swap_list_filenodes((*begin), (*val));
	*val_save = (*begin);
	*val = (*begin)->prev;
}

int			sorting(t_twlist **begin, int (cmp(t_filenode *, t_filenode *)))
{
	t_twlist	*max;
	t_twlist	*min;
	t_twlist	*to_iter;
	t_twlist	*max_save;
	t_twlist	*min_save;

	max_save = NULL;
	min_save = NULL;
	to_iter = *begin;
	max = *begin;
	min = *begin;
	while (max_save != min_save || (max == *begin && min == *begin))
	{
		get_max(&to_iter, &max, &max_save, cmp);
		if (max_save == min_save)
			break ;
		get_min(&to_iter, &min, &min_save, cmp);
	}
	return (0);
}
