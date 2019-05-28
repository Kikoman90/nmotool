/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:40:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/28 19:55:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
	// get sectname
	// -> either get_safe(offset, 16);
	// -> or send t_section as parameter and use section_funk
}
