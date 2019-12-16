/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:46:23 by mflannel          #+#    #+#             */
/*   Updated: 2019/12/16 20:13:28 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		get_index(char *name, int i)
{
	if (g_t_flag)
		return (0);
	if ((int)name[i] > 249 || (int)name[i] < 0)
		return (250);
	return ((name[i]));
}

void	swap_tlist(t_list *one, t_list *two)
{
	void	*i;

	if (!one || !two)
		return ;
	i = one->content;
	one->content = two->content;
	two->content = i;
}

void	range_int_rev(t_list **all)
{
	t_list		*tmp;

	tmp = *all;
	while (tmp && tmp->next)
	{
		if (*(int *)tmp->content > *(int *)tmp->next->content)
		{
			swap_tlist(tmp, tmp->next);
			tmp = *all;
		}
		else
			tmp = tmp->next;
	}
}

void	range_int(t_list **all)
{
	t_list		*tmp;

	if (g_rev_flag == 1)
		return (range_int_rev(all));
	tmp = *all;
	while (tmp && tmp->next)
	{
		if (*(int *)tmp->content < *(int *)tmp->next->content)
		{
			swap_tlist(tmp, tmp->next);
			tmp = *all;
		}
		else
			tmp = tmp->next;
	}
}
