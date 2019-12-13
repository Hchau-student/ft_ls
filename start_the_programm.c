/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_programm.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 14:48:29 by hchau             #+#    #+#             */
/*   Updated: 2019/12/11 23:14:10 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
void		put_names(t_twlist *lst, int total)
{
    if (!lst || !lst->content)
        return ;
    if (g_l_flag == 1)
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
    }
}
struct winsize *get_terminal_props(void)
{
    struct winsize window;
    struct winsize *window_ptr = &window;
    ioctl(0, TIOCGWINSZ, &window_ptr);
    return (window_ptr);
}
int count_nodes(t_twlist *names)
{
    t_twlist *tmp;
    int i;
    tmp = names;
    i = 0;
    while (tmp)
    {
        tmp->next;
        i++;
    }
    return (i);
}
void fill_with_spaces(char *buff, unsigned short columns)
{
    int i;
    i = 0;
    buff[i] = ' ';
    i++;
    while (buff[i] != '\0')
    {
        if (i % g_name_delimiter == 0 && i / columns == g_name_delimiter)
            buff[i] = '\n';
        else
            buff[i] = ' ';
        i++;
    }
}
t_twlist *jump(unsigned short rows_got, t_twlist *name) //Прыгаем на элемент, который должен стоять в одной линии с текущим
{
    t_twlist *current = name;
    int nodes = count_nodes(name);
    int lines = rows_got / nodes;
    while(lines != 0)
    {
        current = current->next;
        lines--;
    }
    return (current);
}
unsigned short get_field_props(unsigned short win_columns, int name_delimiter) //Считаем, сколько колонн у нас влезет
{
    int columns_got = 1;
    while ((((name_delimiter + 2) * columns_got) / win_columns) > 1)
        columns_got++;
    return(columns_got);
}
void jump_back(t_twlist *names) //Прыгаем на элемент, идущий следующим после текущего
{
    while(names->prev)
        names = names->prev;
    names->next;
}
void multicoloumns(t_twlist *names)
{
    int i;
    int c;
    int rows_got;
    char *buff;                                                                     //буффер
    char *extra;                                                                    //доп. указатель на буффер
    struct winsize *win_props;                                                      //указатель на параметры окна
    win_props = get_terminal_props();                                               //Вынимаем параметры окна
    rows_got = get_field_props(win_props->ws_col, g_name_delimiter);                //считаем количество столбцов
    i = count_nodes(names);                                                         //Считаем количество имен
    if(!(buff = (char *)malloc(i * (g_name_delimiter + 2))))                        //выделяем память под буффер
        return ;
    fill_with_spaces(buff, win_props->ws_col);                                      //Заполняем буффер пробелами
    extra = buff;                                                                   //присваиваем доп. указателю адрес буффера
    i = rows_got;
    while (names)
    {
        while (i != 0)
        {
            c = g_name_delimiter -
                ft_strlen(((t_filenode *) names->content)->name);                   //считаем, где начинается новая строчка
            extra = ft_strcpy_return(extra,((t_filenode *) names->content)->name);  //заполняем текущ. имя в буффер
            while (c != 0) {
                extra++;
                c--;
            }
            names = jump(rows_got, names);                                          //прыгаем на следующую колонку
            jump_back(names);                                                       //Прыгаем назад + 1 вперед на след элемент
            i--;
        }
    }
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