//
// Created by Hugor Chau on 2019-09-18.
//

#include "../includes/ft_ls.h"
#include <stdio.h>
#include "../libft/libft.h"
void    fill_len_nuls(int count)
{
    if (count != 5)
        return ;
    spaces_for_links = 0;
    spaces_for_uid = 0;
    spaces_for_grid = 0;
    spaces_for_size = 0;
    spaces_for_time = 0;
}

void    count_max_len(t_filenode *inf)
{
    int     amounths_of_links;
    int     user_id;
    int     group_id;
    int     size;

    amounths_of_links = ft_strlen((inf)->amounths_of_links);
    user_id = ft_strlen((inf)->user->pw_name);
    group_id = ft_strlen((inf)->group->gr_name);
    size = ft_strlen((inf)->size);
    if (spaces_for_links <= amounths_of_links)
        spaces_for_links = amounths_of_links;
    if (spaces_for_uid < user_id)
        spaces_for_uid = user_id;
    if (spaces_for_grid < group_id)
        spaces_for_grid = group_id;
    if (spaces_for_size < size)
        spaces_for_size = size;
}
