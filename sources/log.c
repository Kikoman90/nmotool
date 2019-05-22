/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:16:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/22 20:07:06 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static char	const *err_map[ERR_N] = {
	"invalid file",
	"mmap failed",
	"munmap failed",
	""
};

// invalid_file : bad string index in stringtable ->   
//  -> in _fill_sym_array
//  -> in _manage_sym_arr
//  -> in _manage_lc_symtab
//  -> in _handle
//  -> in _manage_handle

bool	log_error(unsigned int type, char const *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		ft_putstr_fd(2, " : ");
		if (err)
			ft_putstr_fd(2, err);
		if (from)
		{
			(err) ? ft_putstr_fd(2, " ") : ft_putstr_fd(2, "\t");
			ft_putstr_fd(2, from);
		}
		ft_putstr_fd(2, NMO_CLR_OUT);
	}
	return (false);
}

/*int		ft_logF_error(unsigned int type, char *err, char const *from)
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
}*/

void	*log_error_null(unsigned int type, char const *err, char const *from)
{
	if (NMOTOOL_DEBUG)
	{
		ft_putstr_fd(2, NMO_ERR_OUT);
		if (type < ERR_N)
			ft_putstr_fd(2, err_map[type]);
		ft_putstr_fd(2, " : ");
		if (err)
			ft_putstr_fd(2, err);
		if (from)
		{
			(err) ? ft_putstr_fd(2, " ") : ft_putstr_fd(2, "\t");
			ft_putstr_fd(2, from);
		}
		ft_putstr_fd(2, NMO_CLR_OUT);
	}
	return (NULL);
}

/*void	*ft_logF_error_null(unsigned int type, char *err, char const *from)
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
}*/



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
