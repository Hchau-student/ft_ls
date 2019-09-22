#include "../includes/ft_ls.h"
#include <stdio.h>
#include "../libft/libft.h"
void    put_names(t_list *lst, int total)
{
    if (!lst)
        return ;
    if (l_flag == 1)
        print_total(total);
    while (lst)
    {
        if (l_flag == 1)
        {
			print_extra_info(lst);
			ft_putchar(' ');
        }
        ft_putstr(((t_filenode *)lst->content)->name);
        if (l_flag == 1)
        {
            if (((t_filenode *)lst->content)->type_of_file == 10)
                print_link(((t_filenode *)lst->content)->name_for_link);
        }
        ft_putchar('\n');
        lst = lst->next;
    }
    //ft_putchar('\n');
}

int         start_the_programm(char *filename)
{
    t_list      *first_look;
    int         total;

    total = simple_ls(filename, &first_look);
    put_names(first_look, total);
    if (R_flag == 1)
        if ((R_function(first_look, filename)) == -1)
            ft_putendl("Error read");
    ft_lstdel(&first_look, clear_filenode);
    return (0);
}
