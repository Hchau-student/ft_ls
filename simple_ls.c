#include "ft_ls.h"
//какие ошибки могут быть в функции? чтение,

t_list      *reading_from_directories(DIR * dir_fd, char *name)
{
	struct dirent   *res;
	t_list          *dir_content;
	t_filenode      *file_inf;
	char 			*to_free;
	int             spaces_for_links;

	dir_content = NULL;
	name = ft_strjoin(name, "/");
	spaces_for_links = 0;
	while ((res = readdir(dir_fd)))
	{
		to_free = ft_strjoin(name, res->d_name);
		file_inf = create_simplenode(res->d_type, res->d_name, to_free);
		ft_lstpush(&dir_content, ft_lstnew(file_inf, sizeof(t_filenode)));
		clear_filenode2(&file_inf);
		ft_strdel(&to_free);
		//должно быть выравнено по длинне имени, с пробелами кратно 8
	}
	ft_strdel(&name);
	sort(&dir_content);
	return (dir_content);
}

t_list       *simple_ls(char *name)
{
    DIR             *dir_fd;
    t_list          *dir_content;
    t_filenode      *file_inf;
    char 			*to_free;
    int             spaces_for_links;

    if (!(dir_fd = opendir(name)))
    {
        ft_putstr("Error");
        return (NULL);
        //обработать ошибку чтения
    }
    dir_content = reading_from_directories(dir_fd, name);
    if (!(closedir(dir_fd))) //обработать ошибку закрытия фд
        ;
    return (dir_content);
}
