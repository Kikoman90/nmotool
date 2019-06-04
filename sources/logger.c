/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:55:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 18:45:46 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.h"

char		*log_from(char const *file, char const *func, uint32_t line)
{
	return ((NMO_DEBUG) ? ft_strjoin_rf("{", \
		ft_strjoin_rf(file, \
		ft_strjoin_rf(":", \
		ft_strjoin_rf(func, \
		ft_strjoin_rf(":", \
		ft_strjoin_lf(ft_itoa(line), "} ")))))) : NULL);
}

static void	log_display(t_error_type type, char const *err, char *from)
{
	static uint32_t				indent_level = 0;
	static char const			indent_ch = '\t';
	static char const *const	err_map[ERR_N] = { "[invalid file] ", \
		"[mmap failure] ", "[munmap failure] ", "[malloc failure] ", "" };

	if (type < ERR_THROW)
	{
		indent_level = 0;
		ft_putstr_fd(2, ERROR_CLR);
		ft_putstr_fd(2, "ERROR");
		ft_putstr_fd(2, CLEAR_CLR);
	}
	write(2, &indent_ch, indent_level++);
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
