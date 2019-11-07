/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_up.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:46:52 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:46:54 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/libft.h"

void		clear_filenode(void *file, size_t size)
{
	if (size == 0)
		return ;
	if (g_l_flag == 1 || g_t_flag)
	{
		ft_strdel(&((t_filenode *)file)->amounths_of_links);
		ft_strdel(&((t_filenode *)file)->size);
		ft_strdel(&((t_filenode *)file)->groupname);
		ft_strdel(&((t_filenode *)file)->username);
		if (((t_filenode *)file)->type_of_file == LINK_TYPE)
			ft_strdel(&(((t_filenode *)file)->name_for_link));
	}
	ft_strdel(&(((t_filenode *)file)->name));
}

void		clear_filenode_name(void *file, size_t size)
{
	if (size == 0)
		return ;
	ft_strdel(&(((t_filenode *)file)->name));
}

void 		clear_l_in_recoursive(t_twlist **file)
{
	t_twlist		*tmp;
	int 			flag = 0;

	if (!file || !*file)
		return ;
	while (*file && flag == 0)
	{
		if (!(*file)->next)
			flag = 1;
		if (g_l_flag == 1 || g_t_flag)
		{
			ft_strdel(&((t_filenode *)(* file)->content)->amounths_of_links);
			ft_strdel(&((t_filenode *)(*file)->content)->size);
			ft_strdel(&((t_filenode *)(*file)->content)->groupname);
			ft_strdel(&((t_filenode *)(*file)->content)->username);
			if (((t_filenode *)(*file)->content)->type_of_file == LINK_TYPE)
				ft_strdel(&(((t_filenode *)(*file)->content)->name_for_link));
		}
		if (((t_filenode *)(*file)->content)->type_of_file != FOLDER)
		{
			if ((*file)->prev)
				tmp = (*file)->prev;
			else
				tmp = (*file)->next;
			if ((*file)->prev)
				(*file)->prev->next = (*file)->next;
			if ((*file)->next)
				(*file)->next->prev = (*file)->prev;
			ft_twlstdelone(file, clear_filenode_name);
			(*file) = tmp;
			continue ;
		}
		if ((*file) && (*file)->next)
			(*file) = (*file)->next;
	}
	while ((*file) && (*file)->prev)
		(*file) = (*file)->prev;
}