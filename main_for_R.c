#include "../includes/ft_ls.h"
#include "../libft/libft.h"

void    recodnise_dirname(char *name)
{
    if ((is_filename(name)) == -1)
    {
        write (1, "ft_ls: ", 7);
        ft_putstr(name);
        write(1, ": Permission denied\n", 20);
    }
    else
        start_the_programm(name);
}

int     is_filename(char *name)
{
    DIR             *to_open;
    struct stat		box;

    if (!(to_open = opendir(name)))
    {
    	if (!(stat(name, &box)))
			return (-3);
    	if (!(S_IFDIR & box.st_mode))
        	return (-2);
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
                write(1, "illegal option -- ", 18);
                ft_putchar(flag_or_filename[i][j]);
                write(1, "\n", 1);
                write(1, "usage: ft_ls [-Ralrt] [file ...]", 32);
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
            write (1, ":\n", 2);
            recodnise_dirname(flag_or_filename[i]);
            if ((flag_or_filename[i + 1]))
                write(1, "\n", 1);
            i++;
        }
    }
    return (0);
}

//имя файла - проверить, возможно ли сделать это, не валидируя - имя файла, права доступа; сначала - сообщение об ошибке, потом - работа лс
