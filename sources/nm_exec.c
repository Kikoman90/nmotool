/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 10:01:34 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:09:40 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static bool	manage_segment(size_t offset, t_funk funk)
{
	uint32_t				cmdsize;
	t_segment_funk			segment_funk;
	t_segment_command const	*ptr_segment_cmd;

	segment_funk = funk.segment();
	if (!(ptr_segment_cmd = get_safe(offset, segment_funk.size_of, BT_TOP)))
		return (log_error(ERR_THROW, "segment command fetch failed", FROM));
	cmdsize = segment_funk.cmdsize(ptr_segment_cmd);
	if (cmdsize < segment_funk.size_of)
		return (log_error(ERR_FILE, "size of segment is invalid", FROM));
	if (!push_bounds(offset + segment_funk.size_of, \
		cmdsize - segment_funk.size_of, BT_TOP))
		return (log_error(ERR_THROW, "failed to push bounds", FROM));
	if (!iterate_sections(segment_funk.nsects(ptr_segment_cmd), \
		(char const *[2]){ NULL, NULL }, funk.section(), \
		&add_section_type_table_entry))
		return (log_error(ERR_THROW, "failed to iterate over sections", FROM));
	pop_bounds(BT_TOP);
	return (true);
}

static bool	extract_nlist(struct symtab_command symtab, uint32_t nsyms,
	t_nlist_funk nlist_funk)
{
	uint32_t		max_name_size;
	char const		*symbol_name;
	t_nlist const	*ptr_nlist;

	if (!(ptr_nlist = get_safe(swap32(symtab.symoff), \
		nsyms * nlist_funk.size_of, BT_MACHO)))
		return (log_error(ERR_THROW, "failed to get nlist array", FROM));
	if (!reset_symbolist(nsyms))
		return (log_error(ERR_THROW, "failed to reset symbolist", FROM));
	while (nsyms--)
	{
		if (!(max_name_size = \
			swap32(symtab.strsize) - nlist_funk.n_strx(ptr_nlist)) \
			|| max_name_size > swap32(symtab.strsize))
			return (log_error(ERR_FILE, "invalid symbol name offset", FROM));
		if (!(symbol_name = get_safe(swap32(symtab.stroff) + \
			nlist_funk.n_strx(ptr_nlist), max_name_size, BT_MACHO)))
			return (log_error(ERR_THROW, "failed to get symbol name", FROM));
		new_symbol(symbol_name, max_name_size, \
			extract_symbol_type(nlist_funk.n_type(ptr_nlist), \
			nlist_funk.n_sect(ptr_nlist), nlist_funk.n_desc(ptr_nlist), \
			nlist_funk.n_value(ptr_nlist)), nlist_funk.n_value(ptr_nlist));
		ptr_nlist = (t_nlist*)((char*)ptr_nlist + nlist_funk.size_of);
	}
	return (true);
}

static bool	manage_symtab(size_t offset, t_funk funk)
{
	struct symtab_command const	*ptr_symtab;

	if (!(ptr_symtab = get_safe(offset, sizeof(*ptr_symtab), BT_TOP)))
		return (log_error(ERR_THROW, "failed to get symtab command", FROM));
	if (swap32(ptr_symtab->stroff) + swap32(ptr_symtab->strsize) < \
		swap32(ptr_symtab->stroff))
		return (log_error(ERR_FILE, "invalid string table info", FROM));
	if (!extract_nlist(*ptr_symtab, swap32(ptr_symtab->nsyms), funk.nlist()))
		return (log_error(ERR_THROW, "failed to extract symbols", FROM));
	return (true);
}

bool		nm_conductor(t_funk funk)
{
	uint32_t			ncmds;
	t_header_funk		header_funk;
	t_mach_header const	*ptr_header;

	set_nm_print_padding(funk.print_padding);
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
	print_symbols();
	destroy_symbolist();
	return (true);
}
