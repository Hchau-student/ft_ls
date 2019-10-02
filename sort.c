#include "../includes/ft_ls.h"
#include "../libft/libft.h"
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

void        swap_list(t_list **before, t_list **one, t_list **two)      //возможно, если я поменяю местами адреса, будет работать быстрее
{
    //t_list      *tmp;

        //tmp = *one;
        (*one)->next = NULL;
        //(*before)->next = NULL;
        (*before)->next = *two;
        (*one)->next = (*two)->next;
        (*two)->next = (*one);
}

int     sorting(t_list **begin, int(cmp(t_filenode *, t_filenode *))) //возможно, следует сделать мёрж сорт
{
    t_list  *first;

    first = (*begin);
    while (first->next)
    {
//        while (cmp((*begin)->content, (*begin)->next->content) > 0)
//        {
//            first = (*begin)->next;
//            (*begin)->next = (*begin)->next->next;
//            first->next = (*begin);
//            *begin = first;
//        }
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
