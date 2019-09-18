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
	char                            *size;
	int                             extraaccess;
	int                             spaces_for_links;
	int                             total;
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

/* * * * добавить в либу! * * * */
void            ft_lstpush(t_list **beginlist, t_list *add);

/* * * * сортировка * * * */
void            sort(t_list **filenode);
int             sorting(t_list **begin, int(cmp(t_filenode *, t_filenode *)));

/* * * * ф-ии сортировки * * * */
int             cmp_filenode_name(t_filenode *one, t_filenode *two);
int             cmp_filenode_name_rev(t_filenode *one, t_filenode *two);
int             cmp_filenode_data(t_filenode *one, t_filenode *two);
int             cmp_filenode_data_rev(t_filenode *one, t_filenode *two);

/* * * * начало программы * * * */
int             start_the_programm(char *name);
int             is_filename(char *name);
int             recodnise_flag(char *flag_line);

/* * * * сам лс * * * */
int             simple_ls(char *name, t_list **dir_content);
int             R_function(t_list *all_files, char *name);
int             create_simplenode(int type, char *name, char *full_name, t_filenode **new);

/* * * * печать * * * */
void            put_names(t_list *lst, int total);
void            print_extra_info(t_list *lst);
void            print_type_and_access(t_extrainf *file_info);
void            print_total(int total);

/* * * * очистка * * * */
void            clear_filenode(t_filenode *file, size_t size);
void            clear_filenode2(t_filenode *file/*, size_t size*/);

#endif