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

int					is_filename(char *name)
{
	DIR				*to_open;

	if (!(to_open = opendir(name)))
		return (-1);
	if (closedir(to_open) == -1)
		ft_putstr("обработать ошибку закрытия");
	return (0);
}

int					see_if_error(char *flag_or_filename, int if_flag)
{
	if (flag_or_filename && if_flag != -2)
	{
		if ((is_filename(flag_or_filename)) == -1)
		{
			write(1, "illegal option -- ", 18);
			ft_putchar(flag_or_filename[if_flag]);
			write(1, "\n", 1);
			write(1, "usage: ft_ls [-Ralrt] [file ...]\n", 33);
			return (1);
		}
	}
	return (0);
}

int					main(int ac, char **flag_or_filename)
{
	int				i;
	int				j;

	i = 1;
	nulg_l_flags(5);
	while (i <= ac && flag_or_filename[i]
			&& (j = recodnise_flag(flag_or_filename[i])) != -1)
	{
		if ((see_if_error(flag_or_filename[i], j)) == 1)
			return (1);
		i++;
	}
	if (i >= ac)
		return (start_the_programm("."));
	while (i < ac && flag_or_filename[i])
	{
		ft_putstr(flag_or_filename[i]);
		write(1, ":\n", 2);
		recodnise_dirname(flag_or_filename[i]);
		if ((flag_or_filename[i + 1]))
			write(1, "\n", 1);
		i++;
	}
	return (0);
}
