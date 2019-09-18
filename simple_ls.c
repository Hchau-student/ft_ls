#include "ft_ls.h"
//какие ошибки могут быть в функции? чтение,

int       reading_from_directories(DIR * dir_fd, char *name, t_list **dir_content)
{
	struct dirent   *res;
	//t_list          *dir_content;
	t_filenode      *file_inf;
	char 			*to_free;
	int             total;

	*dir_content = NULL;
	name = ft_strjoin(name, "/");
	total = 0;
	while ((res = readdir(dir_fd)))
	{
	    if (a_flag == 0 && res->d_name[0] == '.')
	        continue ;
		to_free = ft_strjoin(name, res->d_name);
		total += create_simplenode(res->d_type, res->d_name, to_free, &file_inf);
		ft_lstpush(dir_content, ft_lstnew(file_inf, sizeof(t_filenode)));
		clear_filenode2(&file_inf);
		ft_strdel(&to_free);
		//должно быть выравнено по длинне имени, с пробелами кратно 8
	}
	ft_strdel(&name);
	sort(dir_content);
	return (total);
}

int        simple_ls(char *name, t_list **dir_content)
{
    DIR             *dir_fd;
//    t_list          *dir_content;
    t_filenode      *file_inf;
    char 			*to_free;
    int             total;

    if (!(dir_fd = opendir(name)))
    {
        ft_putstr("Error");
        return (-1);
        //обработать ошибку чтения
    }
    total = reading_from_directories(dir_fd, name, dir_content);
    if (!(closedir(dir_fd))) //обработать ошибку закрытия фд
        ;
    return (total);
}
