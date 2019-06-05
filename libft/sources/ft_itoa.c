/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:44:44 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:41:40 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_digitnb(long int n)
{
	long int	size;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size++);
}

char			*ft_itoa(int n)
{
	char		*fresh;
	long int	n_long;
	long int	length;

	n_long = (long int)n;
	length = ft_digitnb(n_long);
	if (!(fresh = (char *)malloc((length + 1) * sizeof(char))))
		return (NULL);
	fresh[length--] = '\0';
	n_long *= (n_long < 0) ? -1 : 1;
	while (length >= 0)
	{
		fresh[length--] = (n_long % 10) + '0';
		n_long /= 10;
	}
	if (n < 0)
		fresh[0] = '-';
	return (fresh);
}
