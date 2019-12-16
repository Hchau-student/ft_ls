/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:18 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:48:20 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		cmp_filenode_name(t_filenode *one, t_filenode *two)
{
	return ((ft_strcmp(one->name, two->name)));
}

int		cmp_filenode_name_rev(t_filenode *one, t_filenode *two)
{
	return (ft_strcmp(two->name, one->name));
}

int		cmp_filenode_data(t_filenode *one, t_filenode *two)
{
	if (one->mod_time > two->mod_time)
		return (-1);
	if (one->mod_time < two->mod_time)
		return (1);
	return (cmp_filenode_name(one, two));
}

int		cmp_filenode_data_rev(t_filenode *one, t_filenode *two)
{
	if (one->mod_time > two->mod_time)
		return (1);
	if (one->mod_time < two->mod_time)
		return (-1);
	return (cmp_filenode_name_rev(one, two));
}
