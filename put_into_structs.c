#include <sys/stat.h>
#include "ft_ls.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>

//функция для добавления расширенных параметров в структуру
t_extrainf *create_extrainf(char *name, struct stat box)
{
    t_extrainf      *info;
    char            buf[1024];

    info = (t_extrainf *)malloc(sizeof(t_extrainf));
                                                            //если ссылка - readlink?
    info->mod_time_sec = box.st_mtimespec.tv_sec;
	info->mod_time_nsec = box.st_mtimespec.tv_nsec;
	if (l_flag == 1)
	{
		info->access = box.st_mode;
		info->amounths_of_links = ft_itoa(box.st_nlink);
		info->user = getpwuid(box.st_uid);
		info->group = getgrgid(box.st_gid);
		info->size = ft_itoa(box.st_size);
		listxattr(name, buf, 1024, XATTR_NOFOLLOW) > 0 ? info->extraaccess = 1 : 0;
															//getxattr
	}
    return (info);
}

//функция для создания файлноды
int     create_simplenode(int type, char *name, char *full_name, t_filenode **new)
{
    t_filenode      *res;
    int             total;
    t_extrainf	    *to_free;
    struct stat     box;

    *new = (t_filenode *)malloc(sizeof(t_filenode));
    (*new)->name = ft_strdup(name);
    (*new)->type_of_file = type;
    if (l_flag == 1 || t_flag == 1)
    {
        if (!(lstat(full_name, &box)))                               //очистить всё, если не вышло, защита функции
            ;
        total = box.st_blocks;
        (*new)->file_info = create_extrainf(full_name, box);
    }
    return (total);
}

//ft_lstpush
void    ft_lstpush(t_list **beginlist, t_list *add)
{
    if (!add)
        return ;
    add->next = *beginlist;
    *beginlist = add;
}
