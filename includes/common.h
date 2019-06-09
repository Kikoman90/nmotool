/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:42 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:09:23 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "file_info.h"
# include "funk.h"

# define DEFAULT_TARGET "a.out"

# define IS_MH_CIGAM(magic)		(magic == MH_CIGAM || magic == MH_CIGAM_64)
# define IS_FAT_CIGAM(magic)	(magic == FAT_CIGAM || magic == FAT_CIGAM_64)
# define MAGIC_IS_CIGAM(magic)	(IS_MH_CIGAM(magic) || IS_FAT_CIGAM(magic))

# define IS_MH_64(magic)		(magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
# define IS_FAT_64(magic)		(magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
# define MAGIC_IS_64(magic)		(IS_MH_64(magic) || IS_FAT_64(magic))

typedef bool	(*t_conductor)(t_funk);
typedef bool	(*t_command_op)(size_t, t_funk);
typedef void	(*t_section_op)(size_t);

/*
** machop.c		=> 5 functions
*/
bool			iterate_load_commands(uint32_t ncmds, uint32_t target, \
					t_funk funk, t_command_op opera);
bool			iterate_sections(uint32_t nsects, char const *target[2], \
					t_section_funk funk, t_section_op opera);
bool			machopera(char const *filepath, t_conductor ctor);

#endif
