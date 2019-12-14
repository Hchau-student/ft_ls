/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_programm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:29 by hchau             #+#    #+#             */
/*   Updated: 2019/12/14 03:40:45 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
void		put_names(t_twlist *lst, int total)
{
    if (!lst || !lst->content)
        return ;
    /*if (g_l_flag == 1)
        print_total(total);
    while (lst)
    {
        if (g_l_flag == 1 && total != -2)
        {
            print_extra_info(lst);
            ft_putchar(' ');
        }
        ft_putstr(((t_filenode *)lst->content)->name);
        if (g_l_flag == 1 && total != -2)
        {
            if (((t_filenode *)lst->content)->type_of_file == 10)
                print_link(((t_filenode *)lst->content)->name_for_link);
        }
        ft_putchar('\n');
        lst = lst->next;
    }*/

    multicoloumns(lst);
}
int get_terminal_props(void)
{
    struct winsize ws;
    int             num_col;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    num_col = 14;
    num_col = (num_col) ? num_col : 1;
    return (num_col);
}
int count_nodes(t_twlist *names)
{
    t_twlist *tmp;
    int i;
    tmp = names;
    i = 0;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}
void fill_with_spaces(char *buff, int size, int col_got)
{
    int i;
    i = 0;
    buff[i] = ' ';
    i++;
    while (i != size)
    {
        if (i % (col_got * (g_name_delimiter + 1) - col_got) == 0)
        {
            buff[i] = '\n';
        }
        else
            buff[i] = ' ';
        i++;
    }
    buff[i] = '\0';
}
t_twlist *jump(t_twlist *name, int lines) //Прыгаем на элемент, который должен стоять в одной линии с текущим
{
    t_twlist *current = name;

    while(lines != 0)
    {
        if(current->next == NULL)
            return (NULL);
        current = current->next;
        lines--;
    }
    return (current);
}
unsigned short get_field_props(unsigned short win_columns, int name_delimiter) //Считаем, сколько колонн у нас влезет
{
    int columns_got = 1;
    if (win_columns == 0 || win_columns == NULL)
    {
        ft_putstr("Terminal is not opened");
        exit(0);
    }
    while ((((name_delimiter + 1) * columns_got) / win_columns) < 1)
        columns_got++;
    return(columns_got);
}
t_twlist *jump_back(t_twlist *recent, int lines) //Прыгаем на элемент, идущий следующим после текущего
{
    t_twlist *current;
    current = recent;

    while(lines != 1)
    {
        current = current->prev;
        lines--;
    }
    return (current);
}

char *write_to_buffer(char *extra, t_twlist *names)
{
    int c = 0;

    extra = ft_strcpy_return_noterm(extra, ((t_filenode *) names->content)->name);
    c = (g_name_delimiter) - ft_strlen(((t_filenode *) names->content)->name);
    while (c != 0)
    {
        extra++;
        c--;
    }
    if ((*extra) == '\n')
        extra++;
    return(extra);
}

int recursive(t_twlist *names, int first_jump, char *extra, int i, char *buff)
{
    while (names->next)
    {
        if (first_jump == 0) {
            extra = write_to_buffer(extra, names);
            names = jump(names, i);
            extra = write_to_buffer(extra, names);
            first_jump = 1;
            recursive(names, first_jump, extra, i, buff);
        }
        if (first_jump == 1) {
            names = jump_back(names, i);
            extra = write_to_buffer(extra, names);
            names = jump(names, i);
            extra = write_to_buffer(extra, names);
            recursive(names, first_jump, extra, i, buff);
        }
    }
}

void multicoloumns(t_twlist *names)
{
    int i;
    int j = 0;
    int col_got = 0;
    char *buff;                                                                     //буффер
    char *extra;                                                                    //доп. указатель на буффер
    int win_columns;
    int first_jump = 0;
    win_columns = get_terminal_props();                                               //Вынимаем параметры окна
    col_got = get_field_props(win_columns, g_name_delimiter);                //считаем количество столбцов
    i = count_nodes(names);                                                         //Считаем количество имен
    if(!(buff = (char *)malloc(i * (g_name_delimiter + 2))))                        //выделяем память под буффер
        return ;
    fill_with_spaces(buff, i * (g_name_delimiter + 2), col_got);                                      //Заполняем буффер пробелами
    extra = buff;                                                                   //присваиваем доп. указателю адрес буффера
    i = ((count_nodes(names) / col_got));
    recursive(names, first_jump, extra, i, buff);
    ft_putstr(buff);
}
int			start_the_programm(char *filename, int num)
{
    t_twlist		*first_look;
    int				total;
    if (num != 0)
    {
        ft_putstr(filename);
        ft_putstr(":\n");
    }
    if (recodnise_dirname(filename, DIR_EXIST) != DIR_EXIST)
        return (0);
    if ((total = simple_ls(filename, &first_look, filename)) == -1)
        return (0);
    put_names(first_look, total);
    if (g_recoursive_flag == 1)
        if ((recoursive_ls(first_look, filename)) == -1)
            ft_putendl("Error read");
    if (first_look != NULL)
        ft_twlstdel(&first_look, clear_filenode);
    return (0);
}