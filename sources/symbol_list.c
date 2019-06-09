/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:38:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:16:22 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static t_symbolist g_symbolist = { NULL, 0, NO_SYM };

// realloc !!
bool		reset_symbolist(uint32_t nsyms)
{
	if (!(g_symbolist.zone_start = (t_symbol*)\
		realloc(g_symbolist.zone_start, (size_t)nsyms * sizeof(t_symbol))))
		return (log_error(ERR_MALLOC, "failed to realloc symbol list", FROM));
	g_symbolist.cur_free = 0;
	g_symbolist.sorted_list_start = NO_SYM;
	return (true);
}

t_symbol	*get_sorted_symbol_list(void)
{
	return ((g_symbolist.sorted_list_start != NO_SYM) ? \
		g_symbolist.zone_start + g_symbolist.sorted_list_start : NULL);
}

static void	insert_symbol(t_symbol *prev_sym, t_symbol *sym, int64_t sym_offset)
{
	if (prev_sym)
	{
		sym->next = (prev_sym->next) ? -sym_offset + prev_sym->next : 0;
		prev_sym->next = sym_offset;
	}
	else
	{
		if (g_symbolist.sorted_list_start != NO_SYM)
			sym->next = (int64_t)g_symbolist.sorted_list_start - sym_offset;
		g_symbolist.sorted_list_start = sym_offset;
	}
}

void		new_symbol(char const *name, uint32_t max_name_size, char type, \
	uint64_t address)
{
	t_symbol	*tmp;
	t_symbol	*prev_tmp;
	t_symbol	*new_sym;
	int64_t		new_sym_offset;

	new_sym_offset = (int64_t)g_symbolist.cur_free++;
	new_sym = g_symbolist.zone_start + new_sym_offset;
	new_sym->name = name;
	new_sym->max_name_size = max_name_size;
	new_sym->type = type;
	new_sym->address = address;
	new_sym->next = 0;
	prev_tmp = NULL;
	tmp = get_sorted_symbol_list();
	while (tmp && !sort_symbols(new_sym, tmp))
	{
		new_sym_offset -= (prev_tmp) ? \
			prev_tmp->next : g_symbolist.sorted_list_start;
		prev_tmp = tmp;
		tmp = (tmp->next) ? tmp + tmp->next : NULL;
	}
	insert_symbol(prev_tmp, new_sym, new_sym_offset);
}

void		destroy_symbolist(void)
{
	if (g_symbolist.zone_start)
	{
		free(g_symbolist.zone_start);
		g_symbolist.zone_start = NULL;
	}
}
