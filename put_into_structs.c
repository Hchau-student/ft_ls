#include <sys/stat.h>
#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

//функция для добавления расширенных параметров в структуру
t_extrainf *create_extrainf(char *name)
{
    t_extrainf      *info;
    struct stat     box;
    char            buf[1024];

    info = (t_extrainf *)malloc(sizeof(t_extrainf));
    ft_putendl(name);
                                                            //если ссылка - readlink?
    if (!(lstat(name, &box)))                               //очистить всё, если не вышло, защита функции
        ;
    info->mod_time_sec = box.st_mtimespec.tv_sec;
	info->mod_time_nsec = box.st_mtimespec.tv_nsec;
	if (l_flag == 1)
	{
		info->access = box.st_mode;
		info->amounths_of_links = ft_itoa(box.st_nlink);
		info->user = getpwuid(box.st_uid);
		info->group = getgrgid(box.st_gid);
		info->size = box.st_size;
		listxattr(name, buf, 1024, XATTR_NOFOLLOW) > 0 ? info->extraaccess = 1 : 0;
															//getxattr
	}
    return (info);
}

//функция для создания файлноды
t_filenode      *create_simplenode(int type, char *name, char *full_name)
{
    t_filenode  *res;
    t_extrainf	*to_free;

    res = (t_filenode *)malloc(sizeof(t_filenode));
    res->name = ft_strdup(name);
    res->type_of_file = type;
    //if (type == )
    //if (t_flag == 1)
    	res->file_info = create_extrainf(full_name);
    return (res);
}

//ft_lstpush
void    ft_lstpush(t_list **beginlist, t_list *add)
{
    if (!add)
        return ;
    add->next = *beginlist;
    *beginlist = add;
}
