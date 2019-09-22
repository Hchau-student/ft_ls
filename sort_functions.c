#include <sys/stat.h>
#include "../includes/ft_ls.h"
#include <stdio.h>
#include <time.h>
#include "../libft/libft.h"
int     cmp_filenode_name(t_filenode *one, t_filenode *two)
{
    return((ft_strcmp(one->name, two->name)));
}

int     cmp_filenode_name_rev(t_filenode *one, t_filenode *two)
{
    if (ft_strcmp(one->name, two->name) > 0)
        return (0);
    return (1);
}

int     cmp_filenode_data(t_filenode *one, t_filenode *two)				//кажется, проблемы с ссылками!!!!!!
{
    if (one->mod_time_sec < two->mod_time_sec)
        return (1);
    if (one->mod_time_sec == two->mod_time_sec)
    	if (two->mod_time_nsec < one->mod_time_nsec)
    	    return (1);
    return (0);
}

int     cmp_filenode_data_rev(t_filenode *one, t_filenode *two)
{
	if (one->mod_time_sec > two->mod_time_sec)
		return (1);
	if (one->mod_time_sec == two->mod_time_sec)
		if (one->mod_time_nsec > two->mod_time_nsec)
			return (1);
	return (0);
}