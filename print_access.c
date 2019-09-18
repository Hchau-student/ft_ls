#include "ft_ls.h"

void    print_spaces(int amount)
{
    while (amount--)
        ft_putchar(' ');
}


void 	print_access(int access)
{
	S_IRWXU & access ? ft_putchar('r') : ft_putchar('-');
	S_IWUSR & access ? ft_putchar('w') : ft_putchar('-');
	S_IXUSR & access ? ft_putchar('x') : ft_putchar('-');
	S_IRGRP & access ? ft_putchar('r') : ft_putchar('-');
	S_IWGRP & access ?
	ft_putchar('w') : ft_putchar('-');
	S_IXGRP & access ?
	ft_putchar('x') : ft_putchar('-');
	S_IROTH & access ?
	ft_putchar('r') : ft_putchar('-');
	S_IWOTH & access ?
	ft_putchar('w') : ft_putchar('-');
	S_IXOTH & access ?
	ft_putchar('x') : ft_putchar('-');
}

void    print_type_and_access(t_filenode *file_info)
{
	char 	type;

	type = '-';
	if (S_ISDIR(file_info->access))
		type = 'd';
	if (S_ISLNK(file_info->access))
		type = 'l';
	if (S_ISBLK(file_info->access))
		type = 'b';
	if (S_ISCHR(file_info->access))
		type = 'c';
	if (S_ISSOCK(file_info->access))
		type = 's';
	if (S_ISFIFO(file_info->access))
		type = 'p';
	ft_putchar(type);
	print_access(file_info->access);
	if (file_info->extraaccess == 1)
		ft_putchar('@');
	ft_putchar('\t');
}