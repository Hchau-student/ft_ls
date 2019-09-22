#include "../includes/ft_ls.h"
#include "../libft/libft.h"

void    recodnise_dirname(char *name)
{
    if ((is_filename(name)) == -1)
    {
        ft_putstr("ft_ls: ");
        ft_putstr(name);
        ft_putendl(": Permission denied");
    }
    else
        start_the_programm(name);
}

int     is_filename(char *name)
{
    DIR             *to_open;
    //struct stat     box;

    if (!(to_open = opendir(name)))
    {
        return (-1);
    }
    if (closedir(to_open) == -1)
        ft_putstr("обработать ошибку закрытия");
    return (0);
}

int     main(int ac, char **flag_or_filename)
{
    int         i;
    int         j;

    i = 1;
    null_flags(5);
    while (i <= ac && flag_or_filename[i] && (j = recodnise_flag(flag_or_filename[i])) != -2)
    {
        if (flag_or_filename[i] && j != -3)
        {
            if ((is_filename(flag_or_filename[i])) != -3)
            {
                ft_putstr("illegal option -- ");
                ft_putchar(flag_or_filename[i][j]);
                ft_putchar('\n');
                ft_putendl("usage: ft_ls [-Ralrt1] [file ...]");
                return (1);
            }
        }
        i++;
    }
    if (i >= ac)
        start_the_programm(".");
        //отсортировать заголовки, подруга!
    else
    {
        if (! flag_or_filename[i + 1])
            recodnise_dirname(flag_or_filename[i++]);
        while (i < ac && flag_or_filename[i])
        {
            ft_putstr(flag_or_filename[i]);
            ft_putstr (":\n");
            recodnise_dirname(flag_or_filename[i]);
            if ((flag_or_filename[i + 1]))
                ft_putchar('\n');
            i++;
        }
    }
    return (0);
}

//имя файла - проверить, возможно ли сделать это, не валидируя - имя файла, права доступа; сначала - сообщение об ошибке, потом - работа лс