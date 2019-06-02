/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:40:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 17:09:32 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//
#include <mach-o/stab.h>
//

static char section_type_table[255];

void	add_section_type_table_entry(size_t offset)
{
	static uint8_t	section = 0;
	char			*sectname;

	if (offset == 0)
	{
		ft_bzero(section_type_table, 255);
		section = 0;
	}
	sectname = get_safe(offset, 16);
	if (strcmp(sectname, "__text"))
		section_type_table[section++] = 't';
	else if (strcmp(sectname, "__data"))
		section_type_table[section++] = 'd';
	else if (strcmp(sectname, "__bss"))
		section_type_table[section++] = 'b';
	else
		section_type_table[section++] = 's';
}

void	extract_symbol_type(uint8_t type, uint8_t n_sect, uint16_t desc, uint64_t n_value)
{

}

