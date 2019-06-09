/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 03:18:16 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:11:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

uint8_t g_sort_flags = 0;

void		toggle_sort_flag(enum e_sort_flag flag)
{
	g_sort_flags ^= (uint8_t)flag;
}

static bool	sort_alphabetically(t_symbol *sym, t_symbol *cmp, bool reverse)
{
	int	diff;

	diff = ft_strncmp(sym->name, cmp->name, \
		(sym->max_name_size < cmp->max_name_size) ? \
		sym->max_name_size : cmp->max_name_size);
	if (!diff)
	{
		if ((sym->type == 'u' || sym->type == 'U') \
			&& (cmp->type != 'u' && cmp->type != 'U'))
			return (!reverse);
		else if ((sym->type != 'u' && sym->type != 'U') \
			&& (cmp->type == 'u' || cmp->type == 'U'))
			return (reverse);
		return ((!reverse) ? \
			(sym->address < cmp->address) : (sym->address > cmp->address));
	}
	return ((!reverse) ? (diff < 0) : (diff > 0));
}

static bool	sort_numerically(t_symbol *sym, t_symbol *cmp, bool reverse)
{
	if ((sym->type == 'u' || sym->type == 'U') \
		&& (cmp->type != 'u' && cmp->type != 'U'))
		return (!reverse);
	else if ((sym->type != 'u' && sym->type != 'U') \
		&& (cmp->type == 'u' || cmp->type == 'U'))
		return (reverse);
	if (sym->address == cmp->address)
		return (sort_alphabetically(sym, cmp, reverse));
	return ((!reverse) ? \
		(sym->address < cmp->address) : (sym->address > cmp->address));
}

bool		sort_symbols(t_symbol *sym, t_symbol *cmp)
{
	if (g_sort_flags & FLAG_p)
		return (false);
	if (g_sort_flags & FLAG_n)
		return (sort_numerically(sym, cmp, (bool)(g_sort_flags & FLAG_r)));
	return (sort_alphabetically(sym, cmp, (bool)(g_sort_flags & FLAG_r)));
}
