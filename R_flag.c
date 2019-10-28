#include "../includes/ft_ls.h"
#include <stdlib.h>

//Как печатать имя папки?

//корректно ли считывать в буфер и кастовать из него?

int     R_function(t_twlist *all_files, char *name)
{
    char            *all_path;
    t_twlist          *next_dir;
    char            *tmp;
    int             total;

    all_path = ft_strjoin(name, "/");
    while (all_files)
    {
        if (((t_filenode *)all_files->content)->type_of_file == FOLDER)
        {
            if ((ft_strcmp(((t_filenode *)all_files->content)->name, ".") && ft_strcmp(((t_filenode *)all_files->content)->name, "..")))
            {
                tmp = ft_strjoin(all_path, ((t_filenode *)all_files->content)->name);
                write(1, "\n", 1);
                ft_putstr(tmp);
                write(1, ":\n", 2);
                if ((total = simple_ls(tmp, &next_dir, ((t_filenode *)all_files->content)->name)) == -1)
                {
                    ft_strdel(&tmp);
                    all_files = all_files->next;
                    continue;
                }
                put_names(next_dir, total);
                R_function(next_dir, tmp);
                ft_twlstdel(&next_dir, clear_filenode);
                ft_strdel(&tmp);
            }
        }
        all_files = all_files->next;
    }
    ft_strdel(&all_path);
    return (0);
}
