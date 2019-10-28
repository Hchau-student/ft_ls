#ifndef FT_LS_H
#define FT_LS_H

#include "../libft/libft.h"

//дефайн всех типов: дир = 4 и т.д.

//КАК ПАРСИТЬ ФЛАГИ???

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
//#include <stdio.h>
#include <unistd.h>

#define     FOLDER 4
//для -1 или -С флага:
//define SPACE (разделитель для структур - при флаге -1 - \n, при флаге -С - tab)

int      R_flag;
int      r_flag;
int      t_flag;
int      l_flag;
int      a_flag;

int     spaces_for_links;
int     spaces_for_uid;
int     spaces_for_grid;
int     spaces_for_size;
int     spaces_for_time;

#define PARAM int param
#define LINKS spaces_for_links;
#define UID spaces_for_uid;

typedef struct                      s_filenode
{
    char                            *name;
    int                             type_of_file;
    time_t				            mod_time_sec;
    time_t				            mod_time_nsec;
    int 							access;
    char                            *amounths_of_links;
    struct passwd                   *user;
    struct group                    *group;
    char                            *username;
    char                            *groupname;
    char                            *size;
    int                             extraaccess;
    char                            *name_for_link;
}                                   t_filenode;

/*
 * добавить в либу!
 * */
void            ft_lstpush(t_twlist **beginlist, t_list *add);
void            ft_twlstpush(t_twlist **beginlist, t_twlist *add);

/*
 * сортировка
 * */
void            sort(t_twlist **filenode);
int             sorting(t_twlist **begin, int(cmp(t_filenode *, t_filenode *)));

/*
 * ф-ии сортировки
 * */
int             cmp_filenode_name(t_filenode *one, t_filenode *two);
int             cmp_filenode_name_rev(t_filenode *one, t_filenode *two);
int             cmp_filenode_data(t_filenode *one, t_filenode *two);
int             cmp_filenode_data_rev(t_filenode *one, t_filenode *two);

/*
 * начало программы
 * */
int             start_the_programm(char *name);
int             is_filename(char *name);

/* * * * флаги * * * */
int             recodnise_flag(char *flag_line);
void            null_flags(int count);

/*
 * сам лс
 * */
int             simple_ls(char *name, t_twlist **dir_content, char *short_name);
int             R_function(t_twlist *all_files, char *name);
int             create_simplenode(int type, char *name, char *full_name, t_filenode **new);

/* * * * печать * * * */
void            put_names(t_twlist *lst, int total);
void            print_extra_info(t_twlist *lst);
void            print_type_and_access(t_filenode *file_info);
void            print_total(int total);
void            print_with_spaces(int c, int len, char *str);
void            print_link(char *name);

/*      для неверного имени     */
void    recodnise_dirname(char *name);

/* * * * очистка * * * */
void            clear_filenode(void *file, size_t size);
void            clear_filenode2(t_filenode **file/*, size_t size*/);

/* * * * max_len * * * */
void            fill_len_nuls(int count);
void            count_max_len(t_filenode *inf);

#endif
