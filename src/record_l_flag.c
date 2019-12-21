/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_l_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:49:16 by hchau             #+#    #+#             */
/*   Updated: 2019/11/22 17:49:17 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static int		free_and_return_here(t_filenode **to_free)
{
	if (!*to_free || !to_free)
		return (-1);
	if ((*to_free)->name != NULL)
		ft_strdel(&(*to_free)->name);
	if ((*to_free)->name_for_link != NULL)
		ft_strdel(&(*to_free)->name_for_link);
	if ((*to_free)->amounths_of_links != NULL)
		ft_strdel(&(*to_free)->amounths_of_links);
	if ((*to_free)->size != NULL)
		ft_strdel(&(*to_free)->size);
	if ((*to_free)->username != NULL)
		ft_strdel(&(*to_free)->username);
	if ((*to_free)->groupname != NULL)
		ft_strdel(&(*to_free)->groupname);
	if ((*to_free)->fullname != NULL)
		ft_strdel(&(*to_free)->fullname);
	return (-1);
}

void			create_extrainf(char *name, struct stat box, t_filenode **info)
{
	char		buf[1024];

	if (g_u_flag)
		(*info)->mod_time = box.st_atime;
	else
		(*info)->mod_time = box.st_mtime;
	(*info)->access = box.st_mode;
	(*info)->amounths_of_links = ft_itoa(box.st_nlink);
	(*info)->size = ft_itoa(box.st_size);
	(*info)->username = ft_strdup((getpwuid(box.st_uid))->pw_name);
	(*info)->groupname = ft_strdup((getgrgid(box.st_gid))->gr_name);
	(*info)->extraaccess = listxattr(name, buf, 1024, XATTR_NOFOLLOW);
	count_max_len(*info);
}

int				check_type(char *fullname)
{
	struct stat		box;

	lstat(fullname, &box);
	return ((S_IFLNK & box.st_mode) ? LINK_TYPE : FOLDER);
}

int				get_l_flag(t_filenode **new, char *full_name, int type)
{
	struct stat		box;
	char			buf[2000];
	int				ret;
	int				total;

	total = 0;
	if (g_d_flag)
		type = check_type(full_name);
	if (g_l_flag || g_t_flag || g_g_flag || g_colour_flag)
	{
		if (type == LINK_TYPE)
		{
			lstat(full_name, &box);
			ret = readlink(full_name, buf, sizeof(buf));
			buf[ret] = '\0';
			(*new)->name_for_link = ft_strdup(buf);
		}
		else
			stat(full_name, &box);
		total = box.st_blocks;
		if (!(getpwuid(box.st_uid)))
			return (free_and_return_here(new));
		create_extrainf(full_name, box, new);
	}
	return (total);
}
