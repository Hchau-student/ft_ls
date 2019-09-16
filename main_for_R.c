#include "ft_ls.h"

int     main(int ac, char **flag_or_filename)
{
    int         i;

    i = 1;
    if (ac == 1 /* || recodnise_flag(flag_or_filename[i]) == 1 && ac == 2*/)
        start_the_programm("..");//пока файл находится в папке симейка
    if (ac > 1 && recodnise_flag(flag_or_filename[i]) == 1)
    {
        if (ac == 2)
            start_the_programm("..");
        i++;
    }
    if (ac > 1 && recodnise_flag(flag_or_filename[1]) == -1)
    {
        if ((is_filename(flag_or_filename[i])) == -1)
        {
            ft_putendl("usage");
            return (0);
        }
    }
    while (flag_or_filename[i])
        start_the_programm(flag_or_filename[i++]);
    return (0);
}

//имя файла - проверить, возможно ли сделать это, не валидируя - имя файла, права доступа; сначала - сообщение об ошибке, потом - работа лс