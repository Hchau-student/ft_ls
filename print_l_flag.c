#include "ft_ls.h"
#include <stdio.h>


void        print_total(int total)
{
    ft_putstr("total ");
    ft_putnbr(total);
    ft_putchar('\n');
}

void        write_else(t_extrainf *here)
{
	char    **time_res;
	char    *res;
	int     i;

	ft_putendl(here->amounths_of_links);        //PRINTF!!!!!!!
	ft_putendl(here->user->pw_name);
	ft_putendl(here->group->gr_name);
	ft_putendl(here->size);                     //PRINTF!!!!!!
	time_res = ft_strsplit(ctime(&(here->mod_time_sec)), ' ');
	ft_putendl(time_res[2]);
	ft_putendl(time_res[1]);
	i = 0;
	while((time_res[3]+ i) != (ft_strrchr(time_res[3], ':')))
		ft_putchar(time_res[3][i++]);
	ft_putchar('\n');
	ft_freematr(time_res);
	ft_putchar('\n');
}

void		print_extra_info(t_list *lst)
{
    print_type_and_access(((t_filenode *) lst->content)->file_info);

    write_else(((t_filenode *) lst->content)->file_info);
    ft_putchar('\n');
}