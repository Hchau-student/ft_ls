/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:01:19 by hchau             #+#    #+#             */
/*   Updated: 2019/11/06 14:01:22 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_exist(char *name, int type)
{
	if (type == FOLDER)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(name);
		ft_putstr(": Permission denied\n");
	}
	else
		ft_putendl(name);
}

void		print_nonexist(char *name)
{
	ft_putstr("ft_ls: ");
	ft_putstr(name);
	ft_putstr(": No such file or directory\n");
}
