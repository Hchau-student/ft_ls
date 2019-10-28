#include "../includes/ft_ls.h"
#include "../libft/libft.h"
void        sort(t_twlist **filenode)
{
    if (!filenode || !*filenode)
        return ;
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

void        swap_list_filenodes(t_twlist *one, t_twlist *two) //возможно, следует написать универсальную функцию swap_lst
{
    t_filenode  *tmp;

    tmp = ((t_filenode *)one->content);
    one->content = two->content;
    two->content = tmp;
}


//выделить счётчик - по максимальному количеству листов;
//уменьшать счётчик за каждым проходом
//

//или: назначить максимальное и минимальное значения
//кататься по ним до тех пор, пока значение не станет одинаковым (дохожу до центрального листа)
int     sorting(t_twlist **begin, int(cmp(t_filenode *, t_filenode *))) //возможно, следует сделать мёрж сорт
{
    cmp((*begin)->content, (*begin)->content);
    t_twlist    *max;
    t_twlist    *min;
    t_twlist    *to_iter;
    t_twlist    *max_save;
    t_twlist    *min_save;

    max_save = min_save = NULL;
    to_iter = *begin;
    max = *begin;
    min = *begin;
    while (max_save != min_save || (max == *begin && min == *begin))
    {
        while (to_iter && to_iter->next && to_iter->next != max_save)
        {
//            if (!max || !max_save || !to_iter->content)
//                return (0);
            if (cmp(to_iter->content, max->content) > 0)
                max = to_iter;
            to_iter = to_iter->next;
        }
//        if (!to_iter || !to_iter->content)
//            return (0);
        swap_list_filenodes(to_iter, max);
        max_save = to_iter;
        max = to_iter->prev;
//        if (!max || !max_save)
//            return (0);
        if (max_save == min_save)
            break;
        while (to_iter && to_iter->prev && to_iter->prev != min_save)
        {
//            if (!(min || !min_save || !to_iter->content))
//                return (0);
            if (cmp(to_iter->content, min->content) < 0)
                min = to_iter;
            to_iter = to_iter->prev;
        }
//        if (!to_iter || !to_iter->content)
//            return (0);
        swap_list_filenodes(to_iter, min);
        min = to_iter->next;
        min_save = to_iter;
//        if (!(min || !min_save))
//            return (0);
    }
    return (0);
    return (0);
}
