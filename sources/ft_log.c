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

// tmp
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

// tmp
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



// TODO: fonctions a modifier comme ci-dessous:
// ft_log_error(char const *type, char const *err, char const *from)
// {
//	if (type...) -> MACROS
//	if (err...) -> message d'erreur
//	if (from...) -> nom de la fonction "__func__"
// }
//
// ft_logF_error(char const *type, char const *err, char const *from)
// {
//	if (err...) {
//	    ...
//          free(err);
//	}
// }

// exemples d'utilisation: return (ft_log_error_null(ERR_FILE, strerror(errno), __func__));
//			   return (ft_logF_error(ERR_MMAP, ft_strjoin("mmap has failed: ", strerror(errno)), __func__));
