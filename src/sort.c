/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlota <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:11 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:48:13 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		sort(t_twlist **filenode)
{
	if (!filenode || !*filenode)
		return ;
	if (g_rev_flag == 0 && !g_t_flag)
		sorting(filenode, cmp_filenode_name);
	if (g_rev_flag == 1 && !g_t_flag)
		sorting(filenode, cmp_filenode_name_rev);
	if (g_t_flag == 1)
	{
		if (g_rev_flag == 1)
			sorting(filenode, cmp_filenode_data_rev);
		else
			sorting(filenode, cmp_filenode_data);
	}
}

void		swap_list_filenodes(t_twlist *one, t_twlist *two)
{
	void		*tmp;

	if (!one || !two)
		return ;
	tmp = one->content;
	one->content = two->content;
	two->content = tmp;
}

void		get_min(t_twlist **begin, t_twlist **val, t_twlist **val_save,
					int (cmp(t_filenode *, t_filenode *)))
{
	int		flag;

	flag = 0;
	while (*begin && flag == 0)
	{
		if (!(*begin)->prev)
			flag = 1;
		if ((*begin)->prev && (*begin)->prev == *val_save)
			break ;
		if (cmp((*begin)->content, (*val)->content) < 0)
			*val = *begin;
		if (flag == 0)
			*begin = (*begin)->prev;
	}
	swap_list_filenodes((*begin), (*val));
	*val_save = (*begin);
	*val = (*begin)->next;
}

void		get_max(t_twlist **begin, t_twlist **val, t_twlist **val_save,
									int (cmp(t_filenode *, t_filenode *)))
{
	int		flag;

	flag = 0;
	while (*begin && flag == 0)
	{
		if (!(*begin)->next)
			flag = 1;
		if ((*begin)->next && (*begin)->next == *val_save)
			break ;
		if (cmp((*begin)->content, (*val)->content) > 0)
			*val = *begin;
		if (flag == 0)
			*begin = (*begin)->next;
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

	if (!begin || !*begin || !(*begin)->next)
		return (0);
	max_save = NULL;
	min_save = NULL;
	to_iter = *begin;
	max = *begin;
	min = NULL;
	while (max_save != min_save || (max_save == NULL && min_save == NULL))
	{
		get_max(&to_iter, &max, &max_save, cmp);
		if (min == NULL)
			min = to_iter->prev;
		get_min(&to_iter, &min, &min_save, cmp);
	}
	return (0);
}
