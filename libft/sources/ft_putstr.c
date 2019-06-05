/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:47:31 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:03:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}

void	ft_putnstr(char const *str, size_t n)
{
	size_t	len;

	if (str)
	{
		if ((len = ft_strlen(str)) <= n)
			write(1, str, len);
		else
			write(1, str, n);
	}
}

void	ft_putstr_fd(short fd, char const *str)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	ft_putnstr_fd(short fd, char const *str, size_t n)
{
	size_t	len;

	if (str)
	{
		if ((len = ft_strlen(str)) <= n)
			write(fd, str, len);
		else
			write(fd, str, n);
	}
}
