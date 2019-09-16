#include "ft_ls.h"
#include <stdlib.h>

//Как печатать имя папки?

//корректно ли считывать в буфер и кастовать из него?

int     R_function(t_list *all_files, char *name)
{
    char            *all_path;
    t_list          *next_dir;
    char            *tmp;

    all_path = ft_strjoin(name, "/");
    while (all_files)
    {
        if (((t_filenode *)all_files->content)->type_of_file == FOLDER)
        {
            if (((t_filenode *)all_files->content)->name[0] != '.')
            {
                tmp = ft_strjoin(all_path, ((t_filenode *)all_files->content)->name);
                next_dir = simple_ls(tmp);
                ft_putendl(tmp);
                put_names(next_dir);
                R_function(next_dir, tmp);
                ft_lstdel(&next_dir, clear_filenode);
                ft_strdel(&tmp);
            }
        }
        all_files = all_files->next;
    }
    ft_strdel(&all_path);
    return (0);
}

//if (readdir(smth) == 0) //последний уровень
//clean_up;
//рекурсивно вернуться;
//return (0)