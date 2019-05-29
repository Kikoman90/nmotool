/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:16:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 21:00:33 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char const indent_ch = '\t';

static char	const *err_map[ERR_N] = {
	"[invalid file] ",
	"[mmap failure] ",
	"[munmap failure] ",
	"[malloc failure] ",
	""
};

//	ERROR
//	{file : function l5} -> [type: invalid file] bad string index in stringtable
//		{file : function l2} -> could not find string entry
//			{file : function l102} -> some data could not be fetched. aborting...



char	*log_from(char const *file, char const *func, uint32_t line)
{
	return (ft_strjoin_rf("{", ft_strjoin_rf(file, ft_strjoin_rf(":", \
		ft_strjoin_rf(func, ft_strjoin_rf(":", \
		ft_strjoin_lf(ft_itoa(line), "} ")))))));
}

bool	log_error(enum e_error_type type, char const *err, char *from)
{
	static uint32_t indent_level = 0;

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
	return (false);
}
