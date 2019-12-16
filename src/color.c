/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 19:44:00 by mflannel          #+#    #+#             */
/*   Updated: 2019/12/16 19:45:30 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*get_colour(char **str, char *color, char *name)
{
	char	*extra;

	extra = *str;
	extra = ft_strcpy_return(extra, color);
	extra = ft_strcpy_return(extra, name);
	extra = ft_strcpy_return(extra, END_OF_CLR);
	g_print_count += ft_strlen(color) + ft_strlen(END_OF_CLR);
	return (extra);
}

char	*get_coloured_name(char **str, t_filenode *src)
{
	char	*extra;

	extra = *str;
	g_print_count += ft_strlen(src->name) + 1;
	if (g_colour_flag)
	{
		if (src->type_of_file == FOLDER)
		{
			if (src->access & S_IWUSR && src->access
										& S_IWGRP && src->access & S_IWOTH)
				return (extra = get_colour(&extra, DIR_ACCESS_CLR, src->name));
			else
				return (extra = get_colour(&extra, DIR_CLR, src->name));
		}
		else if (src->type_of_file == LINK_TYPE)
			return (extra = get_colour(&extra, LINK_CLR, src->name));
		else if (src->access & S_IXUSR
				|| S_IXGRP & src->access || src->access & S_IXOTH)
			return (extra = get_colour(&extra, REG_ACCESS_CLR, src->name));
	}
	return ((extra = ft_strcpy_return(extra, src->name)));
}
