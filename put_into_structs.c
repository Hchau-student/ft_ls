/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_into_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:44 by hchau             #+#    #+#             */
/*   Updated: 2019/10/28 14:47:45 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../includes/ft_ls.h"
#include "../libft/libft.h"

void			create_extrainf(char *name, struct stat box, t_filenode **info)
{
	char		buf[1024];

	(*info)->mod_time = box.st_mtime;
	(*info)->access = box.st_mode;
	(*info)->amounths_of_links = ft_itoa(box.st_nlink);
	(*info)->user = getpwuid(box.st_uid);
	(*info)->group = getgrgid(box.st_gid);
	(*info)->size = ft_itoa(box.st_size);
	(*info)->username = ft_strdup((*info)->user->pw_name);
	(*info)->groupname = ft_strdup((*info)->group->gr_name);
	listxattr(name, buf, 1024, XATTR_NOFOLLOW) > 0 ?
									(*info)->extraaccess = 1 : 0;
	count_max_len(*info);
}

int				create_simplenode(int type, char *name, char *full_name,
															t_filenode **new)
{
	int			total;
	struct stat	box;
	char		buf[2000];
	int			ret;

	*new = (t_filenode *)malloc(sizeof(t_filenode));
	(*new)->type_of_file = type;
	(*new)->name = ft_strdup(name);
	total = 0;
	if (g_l_flag == 1 || g_t_flag == 1)
	{
		if (type == LINK_TYPE)
		{
			if (!(lstat(full_name, &box)))
				;
			ret = readlink(full_name, buf, sizeof(buf));
			buf[ret] = '\0';
			(*new)->name_for_link = ft_strdup(buf);
		}
		else if (!(stat(full_name, &box)))
			;
		total = box.st_blocks;
		create_extrainf(full_name, box, new);
	}
	return (total);
}

void			ft_twlstpush(t_twlist **beginlist, t_twlist *add)
{
	if (!add)
		return ;
	add->next = *beginlist;
	if (*beginlist != NULL)
		(*beginlist)->prev = add;
	*beginlist = add;
}
