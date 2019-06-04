/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 17:13:05 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "common.h"

/*
** symbol_table.c	=> 1 function
*/
void				add_section_type_table_entry(size_t offset);
void				extract_symbol_type(uint8_t n_type, uint8_t n_sect, \
						uint16_t n_desc, uint64_t n_value);

#endif
