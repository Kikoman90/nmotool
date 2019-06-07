/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/07 14:57:34 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

// #include <mach-o/stab.h>

# include "common.h"

# define NO_SYM UINT64_MAX

typedef struct		s_symbol
{
	char const		*name;
	uint32_t		max_name_size;
	char			type;
	uint64_t		address;
	int64_t			next;
}					t_symbol;

typedef struct		s_symbolist
{
	t_symbol		*zone_start;
	uint64_t		sorted_list_start;
	uint64_t		cur_free;
	size_t			size_of_sym;
}					t_symbolist;

/*
** symbol_table.c	=> 4 functions
*/
void				print_hexa_address(uint64_t addr, uint32_t len);
void				reset_section_type_table(void);
void				add_section_type_table_entry(size_t offset);
char				extract_symbol_type(uint8_t n_type, uint8_t n_sect, \
						uint16_t n_desc, uint64_t n_value);

/*
** symbolist.c		=> 5 functions
*/
bool				reset_symbolist(uint32_t nsyms);
t_symbol			*get_sorted_symbol_list(void);
void				new_symbol(char const *name, uint32_t max_name_size, \
						char type, uint64_t address);
void				destroy_symbolist(void);

#endif
