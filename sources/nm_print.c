/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 09:06:30 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 16:22:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static uint8_t g_print_flags = 0;
static uint32_t g_print_padding = 16;

void		toggle_print_flag(enum e_print_flag flag)
{
	g_print_flags ^= (uint8_t)flag;
}

void		set_nm_print_padding(uint32_t print_padding)
{
	g_print_padding = print_padding;
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
					print_hexa(symbol->address, g_print_padding);
				else
					ft_putnchar(' ', g_print_padding);
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
