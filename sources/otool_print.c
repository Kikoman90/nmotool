/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:58:58 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 16:20:09 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static uint32_t g_print_padding = 16;

void		set_otool_print_padding(uint32_t padding)
{
	g_print_padding = padding;
}

static void	print_content(char const *buf, uint64_t address, uint64_t size)
{
	uint64_t	i;
	uint64_t	j;

	i = 0;
	while (i < size)
	{
		print_hexa(address + i, g_print_padding);
		ft_putchar('\t');
		j = 0;
		while (j < 0x10 && i + j < size)
		{
			print_hexa((uint64_t)buf[i + j++], 2);
			ft_putchar(' ');
		}
		ft_putchar('\n');
		i += 0x10;
	}
}

bool		print_section_content(t_section const *ptr_section, \
	t_section_funk section_funk)
{
	char const	*buf;
	uint64_t	size;

	size = section_funk.size(ptr_section);
	if (!(buf = get_safe(section_funk.offset(ptr_section), size, BT_MACHO)))
		return (log_error(ERR_THROW, "failed to get section content", FROM));
	ft_putendl("Contents of (__TEXT,__text) section");
	print_content(buf, section_funk.addr(ptr_section), size);
	return (true);
}
