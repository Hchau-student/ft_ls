#include "ft_ls.h"
#include <stdio.h>

void    put_names(t_list *lst)
{
    if (!lst)
        return ;
    while (lst)
    {
        ft_putendl(((t_filenode *)lst->content)->name);
        if (l_flag == 1)
			print_extra_info(lst);
        lst = lst->next;
    }
    ft_putchar('\n');
}

int         start_the_programm(char *filename)
{
    t_list      *first_look;

    first_look = simple_ls(filename);
    put_names(first_look);
    if (R_flag == 1)
        if ((R_function(first_look, filename)) == -1)
            ft_putendl("Error read");
    ft_lstdel(&first_look, clear_filenode);
}
