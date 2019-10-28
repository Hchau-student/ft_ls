#include "../includes/ft_ls.h"
#include "../libft/libft.h"

/*void        clear_extrainf(t_extrainf **to_free)
{
	//free(to_free);
    //написать функцию к -l
    return ;
}
*/
void        clear_filenode(void *file, size_t size)
{
    if (size == 0)
        return ;
    if (l_flag == 1)
    {
        if (l_flag == 1)
        {
            ft_strdel(&((t_filenode *)file)->amounths_of_links);
            ft_strdel(&((t_filenode *)file)->size);
            ft_strdel(&((t_filenode *)file)->groupname);
            ft_strdel(&((t_filenode *)file)->username);
            if(((t_filenode *)file)->type_of_file == 10)
                ft_strdel(&(((t_filenode *)file)->name_for_link));
        }
	}
    ft_strdel(&(((t_filenode *)file)->name));
}
