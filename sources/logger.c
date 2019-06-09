/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:55:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 04:55:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

char		*log_from(char const *file, char const *func, uint32_t line)
{
	return ((NMO_DEBUG) ? ft_strjoin_right_free("{", \
		ft_strjoin_right_free(file, \
		ft_strjoin_right_free(":", \
		ft_strjoin_right_free(func, \
		ft_strjoin_right_free(":", \
		ft_strjoin_left_free(ft_itoa(line), "} ")))))) : NULL);
}

static void	log_display(t_error_type type, char const *err, char *from)
{
	static uint32_t				indent_level = 0;
	static char const *const	err_map[ERR_N] = { "[invalid usage] ", \
		"[invalid file] ", "[mmap failure] ", "[munmap failure] ", \
		"[malloc failure] ", "" };

	if (type < ERR_THROW || indent_level == 0)
	{
		indent_level = 0;
		ft_putstr_fd(2, ERROR_CLR);
		ft_putstr_fd(2, "ERROR");
		ft_putstr_fd(2, CLEAR_CLR);
	}
	ft_putnchar_fd(2, '\t', indent_level++);
	if (from)
	{
		ft_putstr_fd(2, from);
		free(from);
	}
	ft_putstr_fd(2, "-> ");
	if (type < ERR_N)
		ft_putstr_fd(2, err_map[type]);
	if (err)
		ft_putstr_fd(2, err);
	ft_putstr_fd(2, "\n");
}

bool		log_error(t_error_type type, char const *err, char *from)
{
	log_display(type, err, from);
	return (false);
}

void		*log_error_null(t_error_type type, char const *err, char *from)
{
	log_display(type, err, from);
	return (NULL);
}
