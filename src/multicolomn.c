/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multicolomn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 00:53:07 by hchau             #+#    #+#             */
/*   Updated: 2019/12/17 00:53:26 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char		*prepare_multicolimn_buff(int count_names, int count_colomns)
{
	char	*buf;
	char	*iter;
	int		i;

	if (!(buf = (char *)malloc(sizeof(char) *
			(count_colomns * (count_names + 1) * g_name_delimiter) + 10000)))
		return (NULL);
	iter = buf;
	i = 0;
	while (count_names > 0)
	{
		while ((long)i < (long)(g_name_delimiter * count_colomns))
		{
			*(iter) = ' ';
			iter++;
			i++;
		}
		i = 0;
		count_names -= count_colomns;
		*iter = '\n';
		iter++;
	}
	*iter = '\0';
	return (buf);
}

int			get_multicolomn_str(t_twlist *lst, char **buf)
{
	int		count_change;
	char	*iter;

	iter = *buf;
	count_change = 0;
	while (lst)
	{
		iter = ft_strcpy_return(iter, ((t_filenode *)lst->content)->name);
		*iter = ' ';
		while (*iter != '\0' && *iter != '\n')
			iter++;
		if (*iter == '\n' && *(iter + 1) != '\0')
			iter += count_change + 1;
		if (*iter == '\0' || *(iter + 1) == '\0')
		{
			count_change += g_name_delimiter;
			iter = *buf + count_change;
		}
		lst = lst->next;
	}
	return (0);
}

int			print_multicolomn(t_twlist *lst)
{
	int			term_long;
	char		*mult_buf;
	int			count_colomn;
	int			count_names;

	g_print_count = 0;
	if (!lst || !lst->content)
		return (0);
	if ((term_long = get_terminal_props()) == 0)
	{
		g_multicolomn_flag = 0;
		return (-1);
	}
	count_colomn = get_correct_space(term_long);
	count_names = count_all_names(lst);
	while (correct_coloumns(count_names, &count_colomn) != 0)
		count_colomn--;
	if (!(mult_buf = prepare_multicolimn_buff(count_names, count_colomn)))
		return (-1);
	get_multicolomn_str(lst, &mult_buf);
	ft_putstr(mult_buf);
	ft_strdel(&mult_buf);
	return (0);
}
