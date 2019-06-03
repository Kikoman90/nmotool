/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:42 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 21:01:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "fileinf.h"
# include "funk.h"

# define DEFAULT_TARGET "a.out"

typedef bool	(*t_conductor)(void);
typedef bool	(*t_command_op)(size_t);
typedef void	(*t_section_op)(size_t);

/*
** machop.c		=> 4 functions
*/
bool						iterate_load_commands(uint32_t ncmds, \
								uint32_t target, t_command_op opera);
bool						iterate_sections(uint32_t nsects, \
								char const *target[2], t_section_funk funk, \
								t_section_op opera);
bool						machopera(size_t dist, size_t length, t_conductor ctor);
bool						play_macho(char const *filepath, t_conductor ctor);


#endif
