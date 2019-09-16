#include "ft_ls.h"

void        sort(t_list **filenode)
{
    if (!r_flag && !t_flag)                                 //обычный порядок по имени
        sorting(filenode, cmp_filenode_name);
    if (r_flag && !t_flag)                                  //реверс по имени
        sorting(filenode, cmp_filenode_name_rev);
    if (!r_flag && t_flag)                                  //обычный порядок по времени
    {
        /*if (l_flag == 1)
            sorting(filenode, cmp_filenode_data);
        else*/
            sorting(filenode, cmp_filenode_data);
    }
    if (r_flag && t_flag)                                   //реверс по времени
    {
    	sorting(filenode, cmp_filenode_data_rev);
    }
}

void        swap_list_filenodes(t_list *one, t_list *two) //возможно, следует написать универсальную функцию swap_lst
{
    t_filenode  *tmp;

    tmp = ((t_filenode *)one->content);
    one->content = two->content;
    two->content = tmp;
}

int     sorting(t_list **begin, int (*cmp)(t_filenode *, t_filenode *)) //возможно, следует сделать мёрж сорт
{
    t_list  *first;

    first = (*begin);
    while (first->next)
    {
        if (cmp(first->content, first->next->content) > 0)
        {
            swap_list_filenodes(first, first->next);
            first = *begin;
        }
        else
            first = first->next;
    }
    return (0);
}
