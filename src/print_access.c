/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:47:24 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 18:27:06 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*print_access(int access, char **buf)
{
	char	*iter;

	iter = *buf;
	*(iter++) = S_IRWXU & access ? 'r' : '-';
	*(iter++) = S_IWUSR & access ? 'w' : '-';
	if (S_ISUID & access)
		*(iter++) = S_IXUSR & access ? 's' : 'S';
	else
		*(iter++) = S_IXUSR & access ? 'x' : '-';
	*(iter++) = S_IRGRP & access ? 'r' : '-';
	*(iter++) = S_IWGRP & access ? 'w' : '-';
	if (S_ISGID & access)
		*(iter++) = S_IXGRP & access ? 's' : 'S';
	else
		*(iter++) = S_IXGRP & access ? 'x' : '-';
	*(iter++) = S_IROTH & access ? 'r' : '-';
	*(iter++) = S_IWOTH & access ? 'w' : '-';
	if (S_ISVTX & access)
		*(iter++) = S_IXOTH & access ? 't' : 'T';
	else
		*(iter++) = S_IXOTH & access ? 'x' : '-';
	return (iter);
}

int		if_acl(char *fullname)
{
	acl_t		bool_acl;

	if (!fullname)
		return (0);
	bool_acl = acl_get_link_np(fullname, ACL_TYPE_EXTENDED);
	if (!bool_acl)
	{
		acl_free(bool_acl);
		bool_acl = NULL;
	}
	if (bool_acl)
	{
		acl_free(bool_acl);
		return (1);
	}
	return (0);
}

char	*print_type_and_access(t_filenode *file_info, char **buf)
{
	char	type;
	char	*iter;

	iter = *buf;
	type = '-';
	type = (S_ISDIR(file_info->access)) ? 'd' : type;
	type = (S_ISLNK(file_info->access)) ? 'l' : type;
	type = (S_ISBLK(file_info->access)) ? 'b' : type;
	type = (S_ISCHR(file_info->access)) ? 'c' : type;
	type = (S_ISSOCK(file_info->access)) ? 's' : type;
	type = (S_ISFIFO(file_info->access)) ? 'p' : type;
	*(iter++) = type;
	iter = print_access(file_info->access, &iter);
	g_print_count += 11;
	if ((file_info)->extraaccess > 0)
		*(iter++) = '@';
	else if (if_acl(file_info->fullname))
		*(iter++) = '+';
	else
		*(iter++) = ' ';
	return (iter);
}
