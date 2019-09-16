#include "ft_ls.h"

void        clear_extrainf(t_extrainf **to_free)
{
	//free(to_free);
    //написать функцию к -l
    return ;
}

void        clear_filenode(t_filenode *file, size_t size)
{
    if (size == 0)
        return ;
    if (file->file_info != NULL)
	  free(file->file_info);
    ft_strdel(&(file->name));
    ft_memdel(file);
}

void        clear_filenode2(t_filenode *file/*, size_t size*/)
{

  ft_strdel(&(file->name));
  ft_memdel(file);
}

/*void        clean_up(t_list **all)
{
    t_list      *tmp;

    while (*all)
    {
        tmp = (*all)->next;
        clear_filenode((*all)->content);
        free((*all)->content);
        free(*all);
        *all = NULL;
        *all = tmp;
    }
}*/
