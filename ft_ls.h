#ifndef FT_LS_H
#define FT_LS_H

#include "libft/libft.h"

//дефайн всех типов: дир = 4 и т.д.

//КАК ПАРСИТЬ ФЛАГИ???

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>

#define     FOLDER 4
//для -1 или -С флага:
//define SPACE (разделитель для структур - при флаге -1 - \n, при флаге -С - tab)

int      R_flag;
int      r_flag;
int      t_flag;
int      l_flag;
int      a_flag;


typedef struct      s_extrainf              /*      для -l    */
{
    unsigned long long				mod_time_sec;
	unsigned long long				mod_time_nsec;
	int 							access;
	char                            *amounths_of_links;
    struct passwd                   *user;
    struct group                    *group;
	off_t                           size;
	int                             extraaccess;
	int                             spaces_for_links;
//    int             				nichego_no_budet_mnogo;
    //total: перед данными файлов вывести общий вес всех файлов в папке
    //тип (бонусы - мажорное/минорное устройство или что?)
    //права доступа
    //размер
    //создатель или владелец? в чём разница?
    //год модификации
    //количество ссылок?
    //месяц модицикации
    //дата модификации
    //время модицикации
}                   t_extrainf;

typedef struct      s_filenode
{
    char            *name;
    int             type_of_file;
	t_extrainf      *file_info;

}                   t_filenode;



t_list          *simple_ls(char *name);
int             R_function(t_list *all_files, char *name);
int             recodnise_flag(char *flag_line);
t_filenode      *create_simplenode(int type, char *name, char *full_name);
void            ft_lstpush(t_list **beginlist, t_list *add);
void            sort(t_list **filenode);
int             sorting(t_list **begin, int(cmp(t_filenode *, t_filenode *)));
int             cmp_filenode_name(t_filenode *one, t_filenode *two);
int             cmp_filenode_name_rev(t_filenode *one, t_filenode *two);
int             cmp_filenode_data(t_filenode *one, t_filenode *two);
int             cmp_filenode_data_rev(t_filenode *one, t_filenode *two);
int             is_filename(char *name);
int             start_the_programm(char *name);
void            put_names(t_list *lst);
void            clear_filenode(t_filenode *file, size_t size);
void            clear_filenode2(t_filenode *file/*, size_t size*/);
void            print_extra_info(t_list *lst);
void            print_type_and_access(t_extrainf *file_info);

#endif