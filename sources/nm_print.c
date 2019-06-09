/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 09:06:30 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:10:45 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint8_t g_print_flags = 0;

void		toggle_print_flag(enum e_print_flag flag)
{
	g_print_flags ^= (uint8_t)flag;
}

static void	print_hexa_address(uint64_t addr, uint32_t len)
{
	static char const hex_string[16] = "0123456789abcdef";

	if (len)
	{
		print_hexa_address(addr / 16, len - 1);
		ft_putchar(hex_string[addr % 16]);
	}
}

static bool	discard_symbol(char type)
{
	return ((!(g_print_flags & FLAG_a) && type == '-') \
		|| (g_print_flags & FLAG_g && !ft_isupper(type)) \
		|| (g_print_flags & FLAG_u && (type != 'U' && type != 'u')) \
		|| (g_print_flags & FLAG_U && (type == 'U' || type == 'u')));
}

void		print_symbols(void)
{
	t_symbol const	*symbol;

	symbol = get_sorted_symbol_list();
	while (symbol)
	{
		if (!discard_symbol(symbol->type))
		{
			if (!(g_print_flags & FLAG_j) && !(g_print_flags & FLAG_u))
			{
				if (symbol->address \
					|| !(symbol->type == 'u' || symbol->type == 'U'))
					print_hexa_address(symbol->address, 16);
				else
					ft_putnchar(' ', 16);
				ft_putchar(' ');
				ft_putchar(symbol->type);
				ft_putchar(' ');
			}
			ft_putnstr(symbol->name, symbol->max_name_size);
			ft_putchar('\n');
		}
		symbol = (symbol->next) ? symbol + symbol->next : NULL;
	}
}