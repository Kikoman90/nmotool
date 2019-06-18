/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:55:13 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 14:39:02 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_H
# define LOGGER_H

# include "../libft/includes/libft.h"

# define FROM log_from(__FILE__, __FUNCTION__, __LINE__)

# ifndef NMO_DEBUG
#  define NMO_DEBUG 0
# endif

# define ERROR_CLR "\033[4;31m"
# define CLEAR_CLR "\033[0m\n"

typedef enum	e_error_type {
	ERR_USAGE = 0,
	ERR_FILE,
	ERR_MMAP,
	ERR_MUNMAP,
	ERR_MALLOC,
	ERR_THROW,
	ERR_N
}				t_error_type;

/*
** logger.c		=> 5 functions
*/
void			print_hexa(uint64_t addr, uint32_t len);
char			*log_from(char const *file, char const *func, uint32_t line);
bool			log_error(t_error_type type, char const *err, char *from);
void			*log_error_null(t_error_type type, char const *err, char *from);

#endif
