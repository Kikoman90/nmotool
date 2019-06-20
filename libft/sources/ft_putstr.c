/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:47:31 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:11:29 by fsidler          ###   ########.fr       */
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
	size_t	i;

	if (str)
	{
		i = 0;
		while (i < n && str[i])
			write(1, &str[i++], 1);
	}
}

void	ft_putstr_fd(short fd, char const *str)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	ft_putnstr_fd(short fd, char const *str, size_t n)
{
	size_t	i;

	if (str)
	{
		i = 0;
		while (i < n && str[i])
			write(fd, &str[i++], 1);
	}
}
