/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:14:17 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 17:50:38 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		get_presort_index(int i, t_list **all_i,
											t_twlist **presort, t_twlist *put)
{
	t_list		*tmp;
	t_list		*ix;

	ix = *all_i;
	if (!ix || *((int *)ix->content) != i)
	{
		tmp = *all_i;
		while (tmp)
		{
			if (*((int *)tmp->content) == i)
				break ;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			ft_lstpush(all_i, ft_lstnew(&i, sizeof(int *)));
			*presort = NULL;
		}
	}
	if (put != NULL)
		ft_twlstpush(presort, put);
	return (0);
}

t_list	*get_next_lst(t_list **cur)
{
	t_list		*tmp;

	tmp = *cur;
	*cur = (*cur)->next;
	free(tmp->content);
	free(tmp);
	return (*cur);
}

void	func_presort(t_twlist **lst, int index)
{
	int			i;
	t_twlist	*presort[251];
	t_twlist	*to_iter;
	t_list		*all_i;
	t_twlist	*nx;

	all_i = NULL;
	if (!(to_iter = *lst) || !to_iter->next)
		return ;
	while (to_iter)
	{
		nx = to_iter->next;
		i = get_index(((t_filenode *)to_iter->content)->name, index);
		get_presort_index(i, &all_i, &presort[i], to_iter);
		to_iter = nx;
	}
	range_int(&all_i);
	while (all_i)
	{
		i = *(int *)all_i->content;
		all_i = get_next_lst(&all_i);
		func_presort(&to_iter, ++index);
		ft_twlstpush_line(&to_iter, presort[i]);
	}
	*lst = to_iter;
}
