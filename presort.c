/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:14:17 by hchau             #+#    #+#             */
/*   Updated: 2019/12/10 18:14:20 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			func_presort(t_twlist **lst, int index)
{
	int 					i;
	t_presort				presort[251];
	t_twlist				*to_iter;
	t_list					*all_i;
	t_list					*tmp;
	t_twlist				*nx;

	all_i = NULL;
	to_iter = *lst;
	if (!to_iter || !to_iter->next)
		return ;
	while (to_iter)
	{
		nx = to_iter->next;
//		to_iter->next = to_iter;
//		to_iter->next = NULL;
//		to_iter->prev = NULL;
		if ((i = get_index(((t_filenode *)to_iter->content)->name, index)) > 249 || i < 0)
		{
			i = 250;
//			ft_twlstdelone(&to_iter, clear_filenode);
//			to_iter = nx;
//			continue ;//запихать в доп. массив
		}
		if (!all_i || *((int *)all_i->content) != i)
		{
			tmp = all_i;
			while (tmp)
			{
				if (*((int *)tmp->content) == i)
					break ;
				tmp = tmp->next;
			}
			if (!tmp)
			{
				presort[i].content = NULL;
				ft_lstpush(&all_i, ft_lstnew(&i, sizeof(int *)));
			}
		}
		ft_twlstpush((t_twlist **)&((presort[i]).content), to_iter);
		to_iter = nx;
	}
	range_int(&all_i);
	to_iter = NULL;
	while (all_i)
	{
		i = *(int *)all_i->content;
		tmp = all_i;
		if (i != -1)
		{
//			func_presort((t_twlist **) &presort[i].content, ++index);
//			ft_twlstpush_line(&to_iter, (t_twlist *)presort[i].content);
			func_presort(&to_iter, ++index);
			ft_twlstpush_line(&to_iter, (t_twlist *)presort[i].content);
		}
		free(tmp->content);
		free(tmp);
		all_i = all_i->next;
	}
	*lst = to_iter;
}
