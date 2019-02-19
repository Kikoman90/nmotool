/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:16:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/02/19 19:28:45 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int		ft_log_error(char const *str1, char const *str2)
{
	if (NMOTOOL_DEBUG)
	{
		if (str1)
			ft_putstr_fd(2, str1);
		if (str2)
			ft_putstr_fd(2, str2);
		ft_putchar_fd(2, '\n');
	}
	return (0);
}

// ft_log_error(char const *type, char const *err, char const *from)
// {
//	if (type...)
//	if (err...)
//	if (from...)
// }
void	*ft_log_error_null(char const *str1, char const *str2)
{
	if (NMOTOOL_DEBUG)
	{
		if (str1)
			ft_putstr_fd(2, str1);
		if (str2)
			ft_putstr_fd(2, str2);
		ft_putchar_fd(2, '\n');
	}
	return (NULL);
}
