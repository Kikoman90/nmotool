/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbolist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:38:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/07 15:22:26 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

//
#include <stdio.h>
//

static t_symbolist g_symbolist = { NULL, 0, NO_SYM, sizeof(t_symbol) };

bool		reset_symbolist(uint32_t nsyms)
{
	if (!(g_symbolist.zone_start = \
		(t_symbol*)realloc(g_symbolist.zone_start, (size_t)nsyms)))
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

/*
** ft_nm has 8 available flags :

** "-a" -- Display  all symbol table entries (normally debugging symbols are not displayed)
** "-g" -- Display only global (external) symbols
** "-p" -- Don't sort; display in symbol-table order
** "-u" -- Display only undefined symbols
** "-U" -- Don't display undefined symbols
** "-j" -- Just display the symbol names (no value or type)
** "-r" -- Sort in reverse order
** "-n" -- Sort numerically (by address) rather than alphabetically

** by default nm sorts alphabetically (by name)
*/

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

bool		compare_symbols(t_symbol *cmp, t_symbol *sym)
{
	return (sym->address < cmp->address);
}

void		display_list(void)
{
	t_symbol	*tmp;

	if ((tmp = get_sorted_symbol_list()))
	{
		ft_putendl("---LIST---");
		printf("start offset is : %llu\n", g_symbolist.sorted_list_start);
		while (tmp)
		{
			printf("SYM: (next is %04lld) %016llu %c %.*s\n", tmp->next, tmp->address, tmp->type, \
				tmp->max_name_size, tmp->name);
			tmp = (tmp->next) ? tmp + tmp->next : NULL;
		}
		ft_putendl("---LIST---\n");
	}
	else
		ft_putendl("EMPTY--LIST\n");
}

void		new_symbol(char const *name, uint32_t max_name_size, char type, \
	uint64_t address)
{
	t_symbol	*tmp;
	t_symbol	*prev_tmp;
	t_symbol	*new_sym;
	int64_t		new_sym_offset;

	printf("new insertion: cur_free is %llu\n", g_symbolist.cur_free);
	printf("new: %016llu %c %.*s\n", address, type, max_name_size, name);
	display_list();
	new_sym_offset = (int64_t)g_symbolist.cur_free++;
	new_sym = g_symbolist.zone_start + new_sym_offset;
	new_sym->name = name;
	new_sym->max_name_size = max_name_size;
	new_sym->type = type;
	new_sym->address = address;
	new_sym->next = 0;
	prev_tmp = NULL;
	tmp = get_sorted_symbol_list();
	while (tmp && !compare_symbols(tmp, new_sym))
	{
		new_sym_offset -= (prev_tmp) ? prev_tmp->next : g_symbolist.sorted_list_start;
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
