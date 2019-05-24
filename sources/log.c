/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:16:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 20:01:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static char	const *err_map[ERR_N] = {
	"[invalid file] ",
	"[mmap failure] ",
	"[munmap failure] ",
	"[malloc failure] "
	""
};

//	ERROR
//	{file : function l5} -> [type: invalid file] bad string index in stringtable
//		{file : function l2} -> could not find string entry
//			{file : function l102} -> some data could not be fetched. aborting...

bool	log_error(enum e_error_type type, char const *err, char const *from, \
			t_error_callback callback)
{
	static uint32_t indent_level = 0;

	if (type < ERR_THROW)
	{
		indent_level = 0;
		ft_putstr_fd(2, ERROR_CLR);
		ft_putstr_fd(2, "ERROR\n");
		ft_putstr_fd(2, CLEAR_CLR);
	}
	write(2, '\t', indent_level++);
	if (from)
		ft_putstr_fd(2, from);
	ft_putstr_fd(2, "-> ");
	if (type < ERR_N)
		ft_putstr_fd(2, err_map[type]);
	if (err)
		ft_pustr_fd(2, err);
	if (callback)
		callback();
	return (false);
}
