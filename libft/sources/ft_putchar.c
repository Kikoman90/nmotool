/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:46:15 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 17:12:20 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c)
{
	write(1, (unsigned char *)&c, 1);
}

void	ft_putnchar(char c, size_t n)
{
	while (n--)
		write(1, (unsigned char *)&c, 1);
}

void	ft_putchar_fd(short fd, char c)
{
	write(fd, (unsigned char *)&c, 1);
}

void	ft_putnchar_fd(short fd, char c, size_t n)
{
	while (n--)
		write(fd, (unsigned char *)&c, 1);
}
