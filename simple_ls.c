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
#include "../libft/libft.h"
#include <dirent.h>

void	clear_tmp_filenode(t_filenode *to_free)
{
	if (to_free != NULL)
	{
		if (g_l_flag == 1 || g_t_flag == 1)
		{
			if (g_l_flag == 1)
			{
				if (to_free->amounths_of_links
							&& to_free->amounths_of_links != NULL)
					ft_strdel(&(to_free)->amounths_of_links);
				if (to_free->size != NULL)
					ft_strdel(&to_free->size);
				if (to_free->type_of_file == 10)
					ft_strdel(&to_free->name_for_link);
			}
		}
		if (to_free->name != NULL)
			ft_strdel(&to_free->name);
	}
}

int		reading_from_directories(DIR *dir_fd, char *name,
												t_twlist **dir_content)
{
	struct dirent	*res;
	t_filenode		*file_inf;
	char			*full_name;
	int				total;

	*dir_content = NULL;
	name = ft_strjoin(name, "/");
	total = 0;
	while ((res = readdir(dir_fd)))
	{
		if (g_a_flag == 0 && res->d_name[0] == '.')
			continue ;
		full_name = ft_strjoin(name, res->d_name);
		total += create_simplenode(res->d_type,
				res->d_name, full_name, &file_inf);
		ft_twlstpush(dir_content, ft_twlstnew(file_inf, sizeof(t_filenode)));
		free(file_inf);
		ft_strdel(&full_name);
	}
	ft_strdel(&name);
	sort(dir_content);
	return (total);
}

int		simple_ls(char *name, t_twlist **dir_content, char *short_name)
{
	DIR			*dir_fd;
	int			total;

	fill_len_nuls(5);
	if ((dir_fd = opendir(name)) == NULL)
	{
		ft_putstr("ft_ls: ");
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
