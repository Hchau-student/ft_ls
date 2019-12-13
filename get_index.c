//
// Created by Hugor Chau on 2019-12-12.
//
#include "ft_ls.h"

int			get_index(char *name, int i)
{
	if (!name)
		return (-1);
	return ((name[i]));
}


void		swap_tlist(t_list *one, t_list *two)
{
	void 	*i;

	if (!one || !two)
		return ;
	i = one->content;
	one->content = two->content;
	two->content = i;
}


void	*range_int(t_list **all)
{
	t_list		*tmp;

	tmp = *all;
	while (tmp && tmp->next)
	{
		if (*(int *)tmp->content < *(int *)tmp->next->content)
		{
			swap_tlist(tmp, tmp->next);
			tmp = *all;
		}
//		else if (*(int *)tmp->content == *(int *)tmp->next->content)
//		{
//			*(int *)tmp->content = -1;
//			tmp = *all;
//		}
		else
			tmp = tmp->next;
	}
}
