/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/07 14:46:50 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// flag handling
// show usage in case of invalid flag or input

// get_sections_types(size_t offset, t_funk funk)
static bool	manage_segment(size_t offset, t_funk funk)
{
	uint32_t				cmdsize;
	t_segment_funk			segment_funk;
	t_segment_command const	*ptr_segment_cmd;

	segment_funk = funk.segment();
	if (!(ptr_segment_cmd = get_safe(offset, segment_funk.size_of, BT_TOP)))
		return (log_error(ERR_FILE, "segment command fetch failed", FROM));
	cmdsize = segment_funk.cmdsize(ptr_segment_cmd);
	if (cmdsize < segment_funk.size_of)
		return (log_error(ERR_FILE, "size of segment is invalid", FROM));
	if (!push_bounds(offset + segment_funk.size_of, \
		cmdsize - segment_funk.size_of, BT_TOP))
		return (log_error(ERR_THROW, "failed to push bounds", FROM));
	if (!iterate_sections(segment_funk.nsects(ptr_segment_cmd), \
		(char const *[2]){ NULL, NULL }, funk.section(), &add_section_type_table_entry))
		return (log_error(ERR_THROW, "failed to iterate over sections", FROM));
	pop_bounds(BT_TOP);
	return (true);
}

static bool extract_nlist(struct symtab_command const symtab, uint32_t nsyms,
	t_nlist_funk nlist_funk)
{
	uint32_t		max_name_size;
	char const		*symbol_name;
	t_nlist const	*ptr_nlist;

	if (!(ptr_nlist = get_safe(symtab.symoff, nsyms * nlist_funk.size_of, \
		BT_MACHO)))
		return (log_error(ERR_FILE, "failed to get nlist array", FROM));
	if (symtab.stroff + symtab.strsize < symtab.stroff)
		return (log_error(ERR_FILE, "invalid string table info", FROM));
	if (!reset_symbolist(nsyms))
		return (log_error(ERR_THROW, "failed to reset symbolist", FROM));
	ft_putendl("OH YEAH! I MEAN CAN IT GET ANY BETTER THAN THIS?");
	while (nsyms--)
	{
		if (!(max_name_size = symtab.strsize - nlist_funk.n_strx(ptr_nlist)) \
			|| max_name_size > symtab.strsize)
			return (log_error(ERR_FILE, "invalid symbol name offset", FROM));
		if (!(symbol_name = get_safe(symtab.stroff + \
			nlist_funk.n_strx(ptr_nlist), max_name_size, BT_MACHO))) // or BT_FILE ? test with fat binary
			return (log_error(ERR_THROW, "failed to get symbol name", FROM));
		new_symbol(symbol_name, max_name_size, \
			extract_symbol_type(nlist_funk.n_type(ptr_nlist), \
			nlist_funk.n_sect(ptr_nlist), nlist_funk.n_desc(ptr_nlist), \
			nlist_funk.n_value(ptr_nlist)), nlist_funk.n_value(ptr_nlist));
		ptr_nlist = (t_nlist*)((char*)ptr_nlist + nlist_funk.size_of);
	}
	ft_putendl("OH NO");
	return (true);
}

// get_symbols(size_t offset, t_funk funk)
static bool	manage_symtab(size_t offset, t_funk funk)
{
	struct symtab_command const	*ptr_symtab;
	
	if (!(ptr_symtab = get_safe(offset, sizeof(*ptr_symtab), BT_TOP)))
		return (log_error(ERR_FILE, "failed to get symtab command", FROM));
	if (!extract_nlist(*ptr_symtab, ptr_symtab->nsyms, funk.nlist()))
		return (log_error(ERR_THROW, "failed to extract symbols", FROM));
	return (true);
}

static void	nm_print(void)
{
	t_symbol const	*symbol;

	symbol = get_sorted_symbol_list();
	while (symbol)
	{
		if (symbol->address || !(symbol->type == 'u' || symbol->type == 'U'))
			print_hexa_address(symbol->address, 16);
		else
			ft_putnchar(' ', 16);
		ft_putchar(' ');
		ft_putchar(symbol->type);
		ft_putchar(' ');
		ft_putnstr(symbol->name, symbol->max_name_size);
		ft_putchar('\n');
		symbol = (symbol->next) ? symbol + symbol->next : NULL;
	}
}

static bool	nm_conductor(t_funk funk)
{
	uint32_t			ncmds;
	t_header_funk		header_funk;
	t_mach_header const	*ptr_header;

	header_funk = funk.header();
	if (!(ptr_header = get_safe(0, header_funk.size_of, BT_MACHO)))
		return (log_error(ERR_THROW, "failed to get macho header", FROM));
	if (!push_bounds(header_funk.size_of, \
		header_funk.sizeofcmds(ptr_header), BT_TOP))
		return (log_error(ERR_THROW, "failed to set command bounds", FROM));
	ncmds = header_funk.ncmds(ptr_header);
	reset_section_type_table();
	if (!iterate_load_commands(ncmds, funk.segment().type_of, funk, \
		&manage_segment))
		return (log_error(ERR_THROW, "failed to iterate over segments", FROM));
	if (!iterate_load_commands(ncmds, LC_SYMTAB, funk, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtabs", FROM));
	pop_bounds(BT_TOP);
	nm_print();
	destroy_symbolist();
	return (true);
}

int			main(int argc, char **argv)
{
	int	ret;

	ret = 1;
	if (argc < 2)
	{
		if (!play_macho(DEFAULT_TARGET, &nm_conductor))
			ret = log_error(ERR_THROW, "nm failure", FROM);
		return (ret);
	}
	while (*++argv)
	{
		if (**argv == '-')
		{
			;
			//if (!nm_set_flag(*argv))
				//ret = log_error(ERR_THROW...)
		}
		else
		{
			ft_putstr(*argv); //
			ft_putstr(":\n"); //
			if (!play_macho(*argv, &nm_conductor))
				ret = log_error(ERR_THROW, "nm failure", FROM);
			ft_putchar('\n'); //

		}
	}
	return (ret);
}
