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

# include <ar.h> //fat_arch32/64

# include "fileinf.h"
# include "funk.h"

# define DEFAULT_TARGET "a.out"

typedef bool	(*t_agent)(void);
typedef void	(*t_funk)(bool);
typedef void	(*t_section_manager)(size_t);
typedef bool	(*t_lc_manager)(size_t);

/*
** macho.c		=> 5 functions
*/
void			set_section_funk(bool is_64);
bool			iterate_load_commands(uint32_t ncmds, uint32_t target, \
					t_lc_manager funk);
bool			iterate_sections(uint32_t nsects, char const *sectname_target, \
					char const *segname_target, t_section_manager funk);
bool			extract_macho(char const *filepath, t_agent agent, t_funk funk);


#endif
