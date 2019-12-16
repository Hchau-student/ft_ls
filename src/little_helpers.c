/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 20:01:51 by mflannel          #+#    #+#             */
/*   Updated: 2019/12/16 20:13:58 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*get_name(char *name)
{
	if (!name)
		return (NULL);
	if ((ft_strcmp(name, "/")) != 0)
		return ((ft_strjoin(name, "/")));
	return (ft_strdup(name));
}

void	correct_sort_rev(t_twlist **lst, int (cmp(t_filenode *, t_filenode *)))
{
	t_twlist	*iter;

	iter = *lst;
	while (iter && iter->next)
	{
		if ((cmp(iter->content, iter->next->content)) > 0)
		{
			swap_list_filenodes(iter, iter->next);
			iter = iter->prev;
		}
		else
			iter = iter->next;
	}
}

void	correct_sort(t_twlist **lst, int (cmp(t_filenode *, t_filenode *)))
{
	t_twlist	*iter;

	iter = *lst;
	if (g_rev_flag)
		return (correct_sort_rev(lst, cmp_filenode_name_rev));
	while (iter && iter->next)
	{
		if ((cmp(iter->content, iter->next->content)) > 0)
		{
			swap_list_filenodes(iter, iter->next);
			iter = iter->prev;
		}
		else
			iter = iter->next;
	}
}

void	get_abc_result(t_twlist *presort[251],
		t_list *all_i, t_twlist **dir_content)
{
	range_int(&all_i);
	while (all_i)
	{
		func_presort(&presort[*(int *)all_i->content], 0);
		ft_twlstpush_line(dir_content, presort[*(int *)all_i->content]);
		all_i = get_next_lst(&all_i);
	}
	correct_sort(dir_content, cmp_filenode_name);
}

void	get_no_sort(t_twlist **dir_content)
{
	t_twlist	*extra;
	t_twlist	*nx;

	extra = *dir_content;
	*dir_content = NULL;
	while (extra)
	{
		nx = extra->next;
		ft_twlstpush(dir_content, extra);
		extra = nx;
	}
}
