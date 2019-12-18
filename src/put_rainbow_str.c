/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_rainbow_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 20:31:09 by hchau             #+#    #+#             */
/*   Updated: 2019/12/18 20:31:11 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#define RED_PRIDE_COLOR			1
#define ORANGE_PRIDE_COLOR		2
#define YELLOW_PRIDE_COLOR		3
#define GREEN_PRIDE_COLOR		4
#define BLUE_PRIDE_COLOR		5
#define PURPLE_PRIDE_COLOR		6

static int		recodnise_color(char color, int *stop)
{
	if (color == RED_PRIDE_COLOR)
	{
		*stop = RED_STOP;
		return (RED_START);
	}
	if (color == ORANGE_PRIDE_COLOR)
	{
		*stop = ORANGE_STOP;
		return (ORANGE_START);
	}
	if (color == YELLOW_PRIDE_COLOR)
	{
		*stop = YELLOW_STOP;
		return (YELLOW_START);
	}
	if (color == GREEN_PRIDE_COLOR)
	{
		*stop = GREEN_STOP;
		return (GREEN_START);
	}
	*stop = color == BLUE_PRIDE_COLOR ? BLUE_STOP : PURPLE_STOP;
	return (color == BLUE_PRIDE_COLOR ? BLUE_START : (PURPLE_START));
}

static int		count_diff(int col, int stop, int len)
{
	return ((stop - col) / len);
}

static void		putcolor(char color, char flag, int len)
{
	static int		set;
	int				stop;
	static int		plus;
	int				col;

	if (flag == 1)
	{
		set = recodnise_color(color, &stop);
		plus = count_diff(set, stop, len);
	}
	ft_putstr("\033[48;2;");
	col = ((set & 0x00FF0000)) >> 16;
	ft_putnbr(col);
	ft_putchar(';');
	col = ((set & 0x0000FF00)) >> 8;
	ft_putnbr(col);
	ft_putchar(';');
	col = ((set & 0x000000FF)) >> 0;
	ft_putnbr(col);
	set += plus;
	ft_putchar('m');
}

static void		set_extra_spases(int *len, int *color, int *is_first)
{
	int		local;

	local = *len;
	while (local > *is_first - 1)
	{
		ft_putchar(' ');
		putcolor(*color, 0, *len);
		local--;
	}
	*is_first = 0;
	*len = get_terminal_props();
	if (*color == PURPLE_PRIDE_COLOR)
		*color = 0;
	ft_putstr(END_OF_CLR);
	ft_putstr(BLACK_TXT_CLR);
}

void			put_gay_str(int color)
{
	int			len;
	char		*iter;
	int			shift;
	int			is_first;

	is_first = 1;
	len = get_terminal_props();
	ft_putstr(BLACK_TXT_CLR);
	putcolor(color, 1, len);
	shift = 0;
	while (g_print_count)
	{
		putcolor(color, 0, len);
		iter = (g_buf + shift);
		if (*iter == '\n' || len == 0)
		{
			set_extra_spases(&len, &color, &is_first);
			putcolor(++color, 1, len);
		}
		write(1, iter, 1);
		g_print_count--;
		shift++;
		len--;
	}
}
