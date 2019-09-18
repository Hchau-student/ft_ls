#include "ft_ls.h"

/*void        clear_extrainf(t_extrainf **to_free)
{
	//free(to_free);
    //написать функцию к -l
    return ;
}
*/
void        clear_filenode(t_filenode *file, size_t size)
{
    if (size == 0)
        return ;
    if (l_flag == 1 || t_flag == 1)
    {
        if (l_flag == 1)
        {
            ft_strdel(&file->amounths_of_links);
            ft_strdel(&file->size);
        }
	}
    ft_strdel(&(file->name));
    ft_memdel(file);
}

void        clear_filenode2(t_filenode *file/*, size_t size*/)
{
    ft_strdel(&(file->name));
    ft_memdel(file);
}
