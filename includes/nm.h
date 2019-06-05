/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:47:46 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

// #include <mach-o/stab.h>

# include "common.h"

/*
** symbol_table.c	=> 4 functions
*/
void				print_hexa_address(uint64_t addr, uint32_t len);
void				reset_section_type_table(void);
void				add_section_type_table_entry(size_t offset);
char				extract_symbol_type(uint8_t n_type, uint8_t n_sect, \
						uint16_t n_desc, uint64_t n_value);

#endif
