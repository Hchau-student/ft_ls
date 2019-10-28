/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_R.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:01 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:03 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include "../libft/libft.h"

void				recodnise_dirname(char *name)
{
	if ((is_filename(name)) == -1)
	{
		ft_putstr("ft_ls: ");
		ft_putstr(name);
		ft_putstr(": Permission denied\n");
	}
	else
		start_the_programm(name);
}

int					is_filename(char *name)
{
	DIR				*to_open;
	struct stat		box;

	if (!(to_open = opendir(name)))
	{
		if (!(stat(name, &box)))
			return (-3);
		if (!(S_IFDIR & box.st_mode))
			return (-2);
		return (-1);
	}
	if (closedir(to_open) == -1)
		ft_putstr("обработать ошибку закрытия");
	return (0);
}

int					main(int ac, char **flag_or_filename)
{
	int				i;
	int				j;

	i = 1;
	nulg_l_flags(5);
	while (i <= ac && flag_or_filename[i]
			&& (j = recodnise_flag(flag_or_filename[i])) != -2)
	{
		if (flag_or_filename[i] && j != -3)
		{
			if ((is_filename(flag_or_filename[i])) != -3)
			{
				write(1, "illegal option -- ", 18);
				ft_putchar(flag_or_filename[i][j]);
				write(1, "\n", 1);
				write(1, "usage: ft_ls [-Ralrt] [file ...]", 32);
				return (1);
			}
		}
		i++;
	}
	if (i >= ac)
		start_the_programm(".");
	else
	{
		if (!flag_or_filename[i + 1])
			recodnise_dirname(flag_or_filename[i++]);
		while (i < ac && flag_or_filename[i])
		{
			ft_putstr(flag_or_filename[i]);
			write(1, ":\n", 2);
			recodnise_dirname(flag_or_filename[i]);
			if ((flag_or_filename[i + 1]))
				write(1, "\n", 1);
			i++;
		}
	}
	return (0);
}
