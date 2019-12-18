/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_programm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:29 by hchau             #+#    #+#             */
/*   Updated: 2019/12/16 19:43:44 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	write_full_buf(char **to_iter)
{
	char	col;

	if (g_gay_flag)
	{
		if (!get_terminal_props())
			g_gay_flag = 0;
		else
			while (g_print_count > 0)
			{
				col = 1;
				while (col <= 6)
				{
					put_gay_str(col);
					col++;
				}
				ft_putstr(END_OF_CLR);
			}
	}
	write(1, g_buf, g_print_count);
	g_print_count = 0;
	*to_iter = g_buf;
}

void	put_names(t_twlist *lst, int total)
{
	char		*to_iter;

	to_iter = g_buf;
	g_print_count = 0;
	if (!lst || !lst->content)
		return ;
	if ((g_l_flag || g_g_flag) && !g_d_flag)
		print_total(total);
	while (lst)
	{
		if ((g_l_flag == 1 || g_g_flag) && total != -2)
			to_iter = print_extra_info(lst, &to_iter);
		to_iter = get_coloured_name(&to_iter, ((t_filenode *)lst->content));
		if ((g_l_flag == 1 || g_g_flag) && (total != -2))
			if (((t_filenode *)lst->content)->type_of_file == LINK_TYPE)
				to_iter = print_link(((t_filenode *)lst->content)->
												name_for_link, &to_iter);
		to_iter = ft_strcpy_return(to_iter, "\n");
		lst = lst->next;
		if (g_print_count >= 2500)
			write_full_buf(&to_iter);
	}
	write_full_buf(&to_iter);
	g_print_count = 0;
}

int		get_d_flag(char *filename)
{
	t_twlist		*first_look;
	t_filenode		*content;

	if ((create_simplenode(FOLDER, filename, filename, &content) == -1))
		return (0);
	first_look = ft_twlstnew(content, sizeof(t_filenode));
	free(content);
	if (first_look != NULL)
	{
		put_names(first_look, 1);
		ft_twlstdel(&first_look, clear_filenode);
	}
	return (0);
}

int		start_the_programm(char *filename, int num)
{
	t_twlist		*first_look;
	int				total;

	if (g_d_flag == 1)
		return (get_d_flag(filename));
	if (num != 0)
	{
		ft_putstr(filename);
		ft_putstr(":\n");
	}
	if (recodnise_dirname(filename, DIR_EXIST) != DIR_EXIST)
		return (0);
	if ((total = simple_ls(filename, &first_look, filename)) == -1)
		return (0);
	if (g_multicolomn_flag == 1)
		print_multicolomn(first_look);
	if (g_multicolomn_flag == 0)
		put_names(first_look, total);
	if (g_recoursive_flag == 1)
		if ((recoursive_ls(first_look, filename)) == -1)
			ft_putendl("Error read");
	if (first_look != NULL)
		ft_twlstdel(&first_look, clear_filenode);
	return (0);
}
