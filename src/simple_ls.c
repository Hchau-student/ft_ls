/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:01 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 20:12:42 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			put_reading_result(char *d_name, int d_type,
												char **name, t_twlist **put)
{
	int			check_return;
	char		*full_name;
	t_filenode	*file_inf;

	if (!(full_name = ft_strjoin(*name, d_name)))
		return (-1);
	if ((check_return = create_simplenode(d_type,
					d_name, full_name, &file_inf)) == -1)
	{
		if (*name != NULL)
			ft_strdel(name);
		if (full_name != NULL)
			ft_strdel(&full_name);
		if (file_inf != NULL)
			free(file_inf);
		return (-1);
	}
	if (full_name != NULL)
		ft_strdel(&full_name);
	ft_twlstpush((t_twlist **)&(*put),
			ft_twlstnew(file_inf, sizeof(t_filenode)));
	free(file_inf);
	return (check_return);
}

static int	free_and_return(char **name, t_twlist **dir_content, int total)
{
	if (*name)
		ft_strdel(name);
	return (total);
}

int			alternative_sort(DIR *dir_fd, char *name,
								t_twlist **dir_content, int total)
{
	struct dirent			*res;
	int						check_return;

	if (!(name = get_name(name)))
		return (-1);
	while ((res = readdir(dir_fd)))
	{
		if ((!g_a_flag && !g_f_flag) && res->d_name[0] == '.')
			continue ;
		if ((check_return = put_reading_result(res->d_name,
						res->d_type, &name, dir_content)) == -1)
			return (-1);
		total += check_return;
	}
	if (g_t_flag || g_u_flag)
	{
		sort(dir_content);
		return (free_and_return(&name, dir_content, total));
	}
	get_no_sort(dir_content);
	return (total);
}

int			abc_sort(DIR *dir_fd, char *name,
		t_twlist **dir_content, int total)
{
	t_twlist				*presort[251];
	struct dirent			*res;
	int						check_return;
	int						i;
	t_list					*all_i;

	if (!(name = get_name(name)))
		return (-1);
	all_i = NULL;
	while ((res = readdir(dir_fd)))
	{
		if ((g_a_flag == 0) && res->d_name[0] == '.')
			continue ;
		i = get_index(res->d_name, 0);
		get_presort_index(i, &all_i, &presort[i], NULL);
		if ((check_return = put_reading_result(res->d_name,
						res->d_type, &name, &presort[i])) == -1)
			return (-1);
		total += check_return;
	}
	get_abc_result(presort, all_i, dir_content);
	return (free_and_return(&name, dir_content, total));
}

int			simple_ls(char *name, t_twlist **dir_content, char *short_name)
{
	DIR			*dir_fd;
	int			total;

	fill_len_nuls(5);
	if ((dir_fd = opendir(name)) == NULL)
	{
		ft_putstr("\n");
		ft_putstr(name);
		ft_putstr(":\n");
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(short_name, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (-1);
	}
	fill_len_nuls(5);
	*dir_content = NULL;
	total = 0;
	if (g_f_flag || g_t_flag || g_u_flag)
		total = alternative_sort(dir_fd, name, dir_content, total);
	else
		total = abc_sort(dir_fd, name, dir_content, total);
	if (!(closedir(dir_fd)))
		;
	return (total);
}
