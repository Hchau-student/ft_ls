#include "ft_ls.h"

int     is_filename(char *name)
{
    DIR     *to_open;

    if (!(to_open = opendir(name)))
        return (-1);
    if (closedir(to_open) == -1)
        ft_putstr("обработать ошибку закрытия");
    return (0);
}
