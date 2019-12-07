/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:01 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:48:02 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			put_reading_result(char *d_name, int d_type, char **name,
													t_filenode **file_inf)
{
	int		check_return;
	char	*full_name;

	if (!d_name)
		return (-1);
	if (!d_name[0])
		return (-1);
	if (!(full_name = ft_strjoin(*name, d_name)))
		return (-1);
	if ((check_return = create_simplenode(d_type,
										d_name, full_name, file_inf)) == -1)
	{
		if (*name != NULL)
			ft_strdel(name);
		if (full_name != NULL)
			ft_strdel(&full_name);
		if (*file_inf != NULL)
			free(*file_inf);
		return (-1);
	}
	if (full_name != NULL)
		ft_strdel(&full_name);
	return (check_return);
}

char		*get_name(char *name)
{
	if (!name)
		return (NULL);
	if ((ft_strcmp(name, "/")) != 0)
		return ((ft_strjoin(name, "/")));
	return (ft_strdup(name));
}

static int	free_and_return(char **name, t_twlist **dir_content, int total)
{
	if (*name)
		ft_strdel(name);
	if (dir_content != NULL)
		sort(dir_content);
	return (total);
}

int			reading_from_directories(DIR *dir_fd, char *name,
												t_twlist **dir_content)
{
	struct dirent	*res;
	t_filenode		*file_inf;
	int				total;
	int				check_return;

	*dir_content = NULL;
	if (!(name = get_name(name)))
		return (-1);
	total = 0;
	while ((res = readdir(dir_fd)))
	{
		file_inf = NULL;
		if (g_a_flag == 0 && res->d_name[0] == '.')
			continue ;
		if ((check_return = put_reading_result(res->d_name,
						res->d_type, &name, &file_inf)) == -1)
			return (-1);
		total += check_return;
		ft_twlstpush(dir_content, ft_twlstnew(file_inf, sizeof(t_filenode)));
		if (file_inf != NULL)
			free(file_inf);
	}
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
		ft_putstr(":\nft_ls: ");
		ft_putstr(short_name);
		ft_putendl(": Permission denied");
		return (-1);
	}
	fill_len_nuls(5);
	total = reading_from_directories(dir_fd, name, dir_content);
	if (!(closedir(dir_fd)))
		;
	return (total);
}
