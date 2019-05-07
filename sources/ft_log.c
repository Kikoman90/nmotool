/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:16:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/03/11 17:51:16 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	const *err_map[ERR_N] = {
	"invalid file",
	"mmap failed",
	"munmap failed",
	"yolo"
};

int		ft_log_error(unsigned int type, char const *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		ft_putstr_fd(2, "[");
		if (from)
		{
			ft_putstr_fd(2, from);
			ft_putstr_fd(2, " - ");
		}
		ft_putstr_fd(2, "ERROR]");
		ft_putstr_fd(2, NMO_CLR_OUT);
		ft_putchar_fd(2, ' ');
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		if (err)
		{
			ft_putstr_fd(2, " -> ");
			ft_putstr_fd(2, err);
		}
	}
	ft_putstr_fd(2, "\n\033[0m");
	return (0);
}

int		ft_logF_error(unsigned int type, char *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		ft_putstr_fd(2, "[");
		if (from)
		{
			ft_putstr_fd(2, from);
			ft_putstr_fd(2, " - ");
		}
		ft_putstr_fd(2, "ERROR]");
		ft_putstr_fd(2, NMO_CLR_OUT);
		ft_putchar_fd(2, ' ');
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		if (err)
		{
			ft_putstr_fd(2, " -> ");
			ft_putstr_fd(2, err);
			free(err);
		}
	}
	ft_putstr_fd(2, "\n\033[0m");
	return (0);
}

void	*ft_log_error_null(unsigned int type, char const *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		ft_putstr_fd(2, "[");
		if (from)
		{
			ft_putstr_fd(2, from);
			ft_putstr_fd(2, " - ");
		}
		ft_putstr_fd(2, "ERROR]");
		ft_putstr_fd(2, NMO_CLR_OUT);
		ft_putchar_fd(2, ' ');
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		if (err)
		{
			ft_putstr_fd(2, " -> ");
			ft_putstr_fd(2, err);
		}
	}
	ft_putstr_fd(2, "\n\033[0m");
	return (NULL);
}

void	*ft_logF_error_null(unsigned int type, char *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		ft_putstr_fd(2, "[");
		if (from)
		{
			ft_putstr_fd(2, from);
			ft_putstr_fd(2, " - ");
		}
		ft_putstr_fd(2, "ERROR]");
		ft_putstr_fd(2, NMO_CLR_OUT);
		ft_putchar_fd(2, ' ');
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		if (err)
		{
			ft_putstr_fd(2, " -> ");
			ft_putstr_fd(2, err);
			free(err);
		}
	}
	ft_putstr_fd(2, "\n\033[0m");
	return (NULL);
}
