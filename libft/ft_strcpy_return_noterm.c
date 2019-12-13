/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_return_noterm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 21:53:19 by hchau             #+#    #+#             */
/*   Updated: 2019/04/18 21:54:05 by hchau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char   *ft_strcpy_return_noterm(char *dest, char const *src)
{
    size_t    a;
    size_t    len;
    a = 0;
    if (dest != src)
    {
        len = ft_strlen(src);
        while (src[a] && a < len)
        {
            dest[a] = src[a];
            a++;
        }
    }
    return (dest + a);
}
