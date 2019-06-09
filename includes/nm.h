/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:04:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

// #include <mach-o/stab.h> ???

# include "common.h"

enum				e_print_flag
{
	FLAG_a = 1 << 0,
	FLAG_g = 1 << 1,
	FLAG_j = 1 << 2,
	FLAG_u = 1 << 3,
	FLAG_U = 1 << 4
};

enum				e_sort_flag
{
	FLAG_n = 1 << 0,
	FLAG_r = 1 << 1,
	FLAG_p = 1 << 2
};

# define NO_SYM		UINT64_MAX

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
}					t_symbolist;

/*
** nm_exec.c		=> 4 functions
*/
bool				nm_conductor(t_funk funk);

/*
** nm_sort.c		=> 4 functions
*/
void				toggle_sort_flag(enum e_sort_flag flag);
bool				sort_symbols(t_symbol *sym, t_symbol *cmp);

/*
** nm_print.c		=> 4 functions
*/
void				toggle_print_flag(enum e_print_flag flag);
void				print_symbols(void);

/*
** symbol_type.c	=> 3 functions
*/
void				reset_section_type_table(void);
void				add_section_type_table_entry(size_t offset);
char				extract_symbol_type(uint8_t n_type, uint8_t n_sect, \
						uint16_t n_desc, uint64_t n_value);

/*
** symbol_list.c	=> 5 functions
*/
bool				reset_symbolist(uint32_t nsyms);
t_symbol			*get_sorted_symbol_list(void);
void				new_symbol(char const *name, uint32_t max_name_size, \
						char type, uint64_t address);
void				destroy_symbolist(void);

#endif
