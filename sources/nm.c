/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 21:01:20 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// flag handling
// show usage in case of invalid flag or input

static bool	manage_segment(size_t offset)
{
	uint32_t			cmdsize;
	t_segment_command	*ptr_segment_cmd;

	if (!(ptr_segment_cmd = get_safe(offset, seg_funk.size_of)))
		return (log_error(ERR_FILE, "segment command fetch failed", FROM));
	cmdsize = seg_funk.cmdsize(ptr_segment_cmd);
	if (cmdsize < seg_funk.size_of)
		return (log_error(ERR_FILE, "size of segment is invalid", FROM));
	if (!push_bounds(get_current_offset() + offset + seg_funk.size_of, \
		cmdsize - seg_funk.size_of))
		return (log_error(ERR_THROW, "failed to push bounds", FROM));
	if (!iterate_sections(seg_funk.nsects(ptr_segment_cmd), NULL, NULL, &add_section_type_table_entry))
		return (log_error(ERR_THROW, "failed to iterate over sections", FROM));
	pop_bounds();
	return (true);
}

static bool	manage_symtab(size_t offset)
{
	uint32_t				nsyms;
	t_nlist					*ptr_nlist;
	t_symbol_info			*symbols;
	struct symtab_command	*ptr_symtab;
	
	if (!(ptr_symtab = get_safe(offset, sizeof(*ptr_symtab))))
		return (log_error(ERR_FILE, "symtab command fetch failed, erroneous info", FROM));
	nsyms = ptr_symtab->nsyms;
	if (!push_bounds(ptr_symtab->symoff, nsyms * nlist_funk.size_of))
		return (log_error(ERR_THROW, "failed to push bounds", FROM));
	if (!(ptr_nlist = get_safe(0, nsyms * nlist_funk.size_of, )))
		return (log_error(ERR_FILE, "nlist fetch failed, erroneous info", FROM));
	pop_bounds();
	// string table : safe, bounds...
	//
	while (nsyms--)
	{
		symbols[ = extract_nlist_symbol_info(nlist_funk.n_type(ptr_nlist), \
			nlist_funk.n_sect(ptr_nlist), nlist_funk.n_desc(ptr_nlist), \
			nlist_funk.n_value(ptr_nlist));
		symbol.max_string_size
		symbol.string
		symbol.
		ptr_nlist = (t_nlist*)((char*)ptr_nlist + nlist_funk.size_of);
	}
	nmprint(symbols, ptr_symtab->ptr_stroff + ptr_symtab->strsize);
	return (true);
}

bool		nm_conductor(t_funk funk)
{
	uint32_t		ncmds;
	t_header_funk	header_funk;
	t_mach_header	*ptr_header;

	header_funk = funk.header();
	if (!(ptr_header = get_safe(0, header_funk.size_of, MACHO)))
		return (log_error(ERR_THROW, "failed to get macho header", FROM));
	if (!push_bounds(header_funk.size_of, header_funk.sizeofcmds(ptr_header), TOP))
		return (log_error(ERR_THROW, "failed to set command bounds", FROM));
	ncmds = header_funk.ncmds(ptr_header);
	if (!iterate_load_commands(ncmds, funk.segment().type_of, &manage_segment))
		return (log_error(ERR_THROW, "failed to iterate over segments", FROM));
	if (!iterate_load_commands(ncmds, LC_SYMTAB, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtabs", FROM));
	pop_bounds(TOP);
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
