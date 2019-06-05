/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:40:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 17:58:12 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint8_t g_section = 0;
static char g_section_type_table[255];

void	print_hexa_address(uint64_t addr, uint32_t len)
{
	static char const hex_string[16] = "0123456789abcdef";

	if (len)
	{
		print_hexa_address(addr / 16, len - 1);
		ft_putchar(hex_string[addr % 16]);
	}
}

void	reset_section_type_table(void)
{
	ft_bzero(g_section_type_table, 255);
	g_section = 0;
}

void	add_section_type_table_entry(size_t offset)
{
	char	*sectname;

	sectname = get_safe(offset, 16, BT_TOP);
	if (!ft_strcmp(sectname, "__text"))
		g_section_type_table[g_section++] = 't';
	else if (!ft_strcmp(sectname, "__data"))
		g_section_type_table[g_section++] = 'd';
	else if (!ft_strcmp(sectname, "__bss"))
		g_section_type_table[g_section++] = 'b';
	else
		g_section_type_table[g_section++] = 's';
}

char	extract_symbol_type(uint8_t n_type, uint8_t n_sect, uint16_t n_desc, \
	uint64_t n_value)
{
	char	type;
	uint8_t	n_type_field;

	n_type_field = n_type & N_TYPE;
	if (n_type & N_STAB)
		type = '-';
	else if (n_type_field == N_UNDF)
		type = n_value ? 'c' : 'u';
	else if (n_type_field == N_ABS)
		type = 'a';
	else if (n_type_field == N_SECT)
	{
		if (n_sect == NO_SECT || !(type = g_section_type_table[n_sect - 1]))
			type = '?';
	}
	else if (n_type_field == N_PBUD)
		type = 'u';
	else if (n_type_field == N_INDR)
		type = 'i';
	else if (n_desc & N_WEAK_REF)
		type = 'W';
	if (N_EXT & n_type)
		type = ft_toupper(type);
	return (type);
}
