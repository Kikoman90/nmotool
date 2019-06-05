/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:46:38 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:04:55 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl(char const *str)
{
	if (str)
	{
		ft_putstr(str);
		ft_putchar('\n');
	}
}

void	ft_putendl_fd(short fd, char const *str)
{
	if (str)
	{
		ft_putstr_fd(fd, str);
		ft_putchar_fd(fd, '\n');
	}
}
