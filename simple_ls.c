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

#include "ft_ls.h"
#include "ft_ls.h"
//
//void			ft_twlstpush_line(t_twlist **beginlist, t_twlist *add)
//{
//	t_twlist	*tmp;
//
//	if (!add)
//		return ;
//	tmp = add;
//	while (tmp->next)
//		tmp = tmp->next;
//	tmp->next = *beginlist;
//	if (*beginlist != NULL)
//		(*beginlist)->prev = tmp;
//	*beginlist = add;
//}

t_twlist	*get_list(t_presort *presort)
{
	t_twlist	*new;
	int 		i;

	new = NULL;
	i = 0;
	while (i < 101)
	{
		if (!(presort[i]).content)
		{
			i++;
			continue ;
		}
		else
		{
			sort((t_twlist **)&presort[i].content);
			ft_twlstpush_line(&new, (t_twlist *)presort[i].content);
		}
		i++;
	}
	return (new);
}

//int			get_index(char *name, int i)
//{
//	if (!name)
//		return (-1);
//	if (g_rev_flag)
//		return (name[i] - 32);
//	if (name - 32 < 0)
//		return (-1);
//	return (100 - (name[i] - 32));
//}

int			put_reading_result(char *d_name, int d_type, char **name, t_presort *put)
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
		file_inf->fullname = full_name;
	ft_twlstpush((t_twlist **)(&(put)->content), ft_twlstnew(file_inf, sizeof(t_filenode)));
//	clear_filenode(&file_inf, sizeof(t_filenode)); //утечки!
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
	return (total);
}

void			correct_sort(t_twlist **lst, int(cmp(t_filenode *, t_filenode *)))
{
	t_twlist	*iter;

	iter = *lst;
	while (iter && iter->next)
	{
		if ((cmp(iter->content, iter->next->content)) > 0)
		{
			swap_list_filenodes(iter, iter->next);
			iter = iter->prev;
		} else
			iter = iter->next;
	}
}

int			reading_from_directories(DIR *dir_fd, char *name,
										t_twlist **dir_content)
{
	t_presort				presort[251];
	struct dirent			*res;
	int						total;
	int						check_return;
	int 					i;
	t_list					*all_i;
	t_list					*tmp;

	if (!(name = get_name(name)))
		return (-1);
	total = 0;
	all_i = NULL;
	while ((res = readdir(dir_fd)))
	{
		if (g_a_flag == 0 && res->d_name[0] == '.')
			continue ;
		if ((i = get_index(res->d_name, 0)) > 249 || i < 0)
			i = 250;
		if (!all_i || *((int *)all_i->content) != i)
		{
			tmp = all_i;
			while (tmp)
			{
				if (*((int *)tmp->content) == i)
					break ;
				tmp = tmp->next;
			}
			if (!tmp)
			{
				presort[i].content = NULL;
				ft_lstpush(&all_i, ft_lstnew(&i, sizeof(int *)));
			}
		}
		if ((check_return = put_reading_result(res->d_name,
											   res->d_type, &name, &presort[i])) == -1)
			return (-1);
		total += check_return;
	}
	range_int(&all_i);
	while (all_i)
	{
		i = *(int *)all_i->content;
		tmp = all_i;
//		if (i != -1)
//		{
			func_presort((t_twlist **) &presort[i].content, 0);
			ft_twlstpush_line(dir_content, (t_twlist *) presort[i].content);
//		}
		free(tmp->content);
		free(tmp);
		all_i = all_i->next;
	}
	correct_sort(dir_content, cmp_filenode_name);
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
	*dir_content = NULL;
	total = reading_from_directories(dir_fd, name, dir_content);
	if (!(closedir(dir_fd)))
		;
	return (total);
}