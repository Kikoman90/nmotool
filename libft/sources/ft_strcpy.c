/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:00:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 18:24:56 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	j = n;
	while (j--)
		((unsigned char*)dest)[j] = '\0';
	i = 0;
	while (n-- && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
