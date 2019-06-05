/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 11:02:37 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:21:26 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char const *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[j])
		j++;
	while (src[i])
		dest[j++] = src[i++];
	dest[j] = '\0';
	return (dest);
}
