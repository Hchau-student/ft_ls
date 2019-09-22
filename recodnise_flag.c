#include "../includes/ft_ls.h"
#include "../libft/libft.h"
/*      
        функция возвращает -1, если есть ошибка в чтении флагов,
                            1, если флаги были введены корректно и
                            0, если первый аргумент не является флагом
                            проблема: найти "illigal option"
*/

/*      
        можно исправить оригинальное поведение лс, если учесть тот факт,
        что имя файла может начинаться с "-"
*/

/*
        прогнать через дебагер: почему не меняется значение статических переменных?
*/

int     recodnise_flag(char *flag_line)
{
    int     i;

    if (flag_line[0] && flag_line[0] != '-')
        return (-2);
    i = 1;
    while (flag_line[i])
    {
        if (flag_line[i] == 'R')
            R_flag = 1;
        else if (flag_line[i] == 'r')
            r_flag = 1;
        else if (flag_line[i] == 'a')
            a_flag = 1;
        else if (flag_line[i] == 't')
            t_flag = 1;
        else if (flag_line[i] == 'l')
            l_flag = 1;
        else if (flag_line[i] == '1')
            ;
        else
            return (i);
        i++;
    }
    return (-3);
}

void    null_flags(int count)
{
    if (count == 5)
    {
        R_flag = 0;
        r_flag = 0;
        t_flag = 0;
        l_flag = 0;
        a_flag = 0;
    }
}
