#include "ft_ls.h"

int     is_filename(char *name)
{
    DIR     *to_open;

    if (!(to_open = opendir(name)))
        return (-1);
    closedir(to_open);
    return (0);
}
