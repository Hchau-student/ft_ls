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

void			ft_twlstpush_line(t_twlist **beginlist, t_twlist *add)
{
	t_twlist	*tmp;

	if (!add)
		return ;
	tmp = add;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = *beginlist;
	if (*beginlist != NULL)
		(*beginlist)->prev = tmp;
	*beginlist = add;
}

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
			ft_twlstpush_line(&new, (t_twlist *)presort[i].content);
		i++;
	}
	return (new);
}

int			get_index(char *name, int i)
{
	if (!name)
		return (-1);
	if (g_rev_flag)
		return (name[i] - 32);
	if (name - 32 < 0)
		return (-1);
	return (100 - (name[i] - 32));
}

int			put_reading_result(char *d_name, int d_type, char **name, t_presort *put, int i)
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
	ft_twlstpush((t_twlist **)(&(put)->content), ft_twlstnew(file_inf, sizeof(t_filenode)));
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
	return (total);
}

void		null_presort(t_presort *to_null)
{
	to_null->content = NULL;
}

int			reading_from_directories(DIR *dir_fd, char *name,
												t_twlist **dir_content)
{
	static t_presort		presort[102];
	struct dirent			*res;
	int						total;
	int						check_return;
	int 					i;

	i = 0;
	while (i != 102)
		null_presort(&presort[i++]);
	if (!(name = get_name(name)))
		return (-1);
//	if (name[0] != '/')		некоторые папки перестают отрабатывать вообще в принципе
//		name[ft_strlen(name) - 1] = '\0';
	total = 0;
	i = 0;
	while ((res = readdir(dir_fd)))
	{
		if (g_a_flag == 0 && res->d_name[0] == '.')
			continue ;
		if (get_index(res->d_name, 0) < 0 || get_index(res->d_name, 0) > 100)
			continue ;//запихать в доп. массив
		if ((check_return = put_reading_result(res->d_name,
						res->d_type, &name, &presort[get_index(res->d_name, 0)], i)) == -1)
			return (-1);
		total += check_return;
		i++;
	}
	i = 0;
	//
	//		У
	//		Б
	//		Р
	//		А
	//		Т
	//		Ь
	//
	//		С
	//		О
	//		Р
	//		Т
	//		И
	//		Р
	//		О
	//		В
	//		К
	//		У
	//		!!!
	while (i != 101)
		sort((t_twlist **)&presort[i++].content);
	*dir_content = get_list(presort);
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
//	if (*dir_content == NULL)
//		return (-1);
	return (total);
}
