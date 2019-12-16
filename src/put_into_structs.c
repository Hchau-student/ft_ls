/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_into_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:44 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:45 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void			prepare_struct(t_filenode **prepare)
{
	(*prepare)->name = NULL;
	(*prepare)->name_for_link = NULL;
	(*prepare)->amounths_of_links = NULL;
	(*prepare)->size = NULL;
	(*prepare)->username = NULL;
	(*prepare)->groupname = NULL;
	(*prepare)->fullname = NULL;
}

int				create_simplenode(int type, char *name, char *full_name,
															t_filenode **new)
{
	*new = (t_filenode *)malloc(sizeof(t_filenode));
	prepare_struct(new);
	(*new)->name = ft_strdup(name);
	(*new)->type_of_file = type;
	if (g_multicolomn_flag)
		compare_names(name);
	(*new)->fullname = ft_strdup(full_name);
	if (g_l_flag || g_t_flag || g_g_flag || g_d_flag)
		return (get_l_flag(new, full_name, type));
	return (0);
}

void			ft_twlstpush(t_twlist **beginlist, t_twlist *add)
{
	if (!add)
		return ;
	add->next = *beginlist;
	if (*beginlist != NULL)
		(*beginlist)->prev = add;
	*beginlist = add;
}

void			ft_twlstpush_line(t_twlist **beginlist, t_twlist *add)
{
	t_twlist	*tmp;

	if (!add)
		return ;
	tmp = add;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *beginlist;
	if (*beginlist != NULL)
		(*beginlist)->prev = tmp;
	*beginlist = add;
}

void			ft_lstpush(t_list **beginlist, t_list *add)
{
	if (!add)
		return ;
	add->next = *beginlist;
	*beginlist = add;
}
