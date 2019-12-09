/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy_return.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflannel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 20:19:17 by mflannel          #+#    #+#             */
/*   Updated: 2019/12/05 20:19:19 by mflannel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../printf_push/libft/libft.h"

char	*ft_strcpy_return(char *dest, char const *src)
{
	size_t		a;
	size_t		len;

	a = 0;
	if (dest != src)
	{
		len = ft_strlen(src);
		while (src[a] && a < len)
		{
			dest[a] = src[a];
			a++;
		}
		dest[a] = '\0';
	}
	return (dest + a);
}
