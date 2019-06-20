/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 16:20:19 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "common.h"

/*
** otool_print.c	=> 3 functions
*/
void				set_otool_print_padding(uint32_t padding);
bool				print_section_content(t_section const *ptr_section, \
						t_section_funk section_funk);

/*
** otool_exec.c		=> 2 functions
*/
bool				otool_conductor(t_funk funk);

#endif
