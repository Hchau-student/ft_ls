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

#include "ft_ls.h"

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
