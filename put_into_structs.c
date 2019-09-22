#include <sys/stat.h>
#include "../includes/ft_ls.h"
#include "../libft/libft.h"
//функция для добавления расширенных параметров в структуру




void        create_extrainf(char *name, struct stat box, t_filenode **info)
{
    char            buf[1024];
                                                            //если ссылка - readlink?
    (*info)->mod_time_sec = box.st_mtimespec.tv_sec;
    (*info)->mod_time_nsec = box.st_mtimespec.tv_nsec;
	if (l_flag == 1)
	{
        (*info)->access = box.st_mode;
        (*info)->amounths_of_links = ft_itoa(box.st_nlink);
        (*info)->user = getpwuid(box.st_uid);
        (*info)->group = getgrgid(box.st_gid);
        (*info)->size = ft_itoa(box.st_size);
		listxattr(name, buf, 1024, XATTR_NOFOLLOW) > 0 ? (*info)->extraaccess = 1 : 0;
        count_max_len(*info);
	}
}

//функция для создания файлноды
int         create_simplenode(int type, char *name, char *full_name, t_filenode **new)
{
    int             total;
    struct stat     box;
    char            buf[1024];
    int             ret;

    *new = (t_filenode *)malloc(sizeof(t_filenode));
    (*new)->name = ft_strdup(name);
    (*new)->type_of_file = type;
    total = 0;
    if (l_flag == 1 || t_flag == 1)
    {
        if (type == 10)
        {
            if (!(lstat(full_name, &box)))                               //очистить всё, если не вышло, защита функции
                ;
            ret = readlink(full_name, buf, sizeof(buf));
            buf[ret] = '\0';
            (*new)->name_for_link = ft_strdup(buf);
        }
        else if (!(stat(full_name, &box)))                               //очистить всё, если не вышло, защита функции
            ;
        total = box.st_blocks;
        create_extrainf(full_name, box, new);
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
