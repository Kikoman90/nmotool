/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:49:45 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:17:37 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*text;

	if (!(text = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_bzero(text, size);
	text[size] = '\0';
	return (text);
}
