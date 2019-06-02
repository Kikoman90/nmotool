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

static t_nlist_funk	nlist_funk;
static t_segment_funk seg_funk;
static t_header_funk hdr_funk;

void		nm_funk(bool is_64)
{
	set_section_funk(is_64);
	if (is_64)
	{
		hdr_funk = (t_header_funk)\
			{ sizeof(struct mach_header_64), &ncmds64, &sizeofcmds64 };
		seg_funk = (t_segment_funk)\
			{ sizeof(struct segment_command_64), &cmdsize64, &nsects64, \
				LC_SEGMENT_64 };
		nlist_funk = (t_nlist_funk){ sizeof(struct nlist_64) };
	}
	else
	{
		hdr_funk = (t_header_funk)\
			{ sizeof(struct mach_header), &ncmds32, &sizeofcmds32 };
		seg_funk = (t_segment_funk)\
			{ sizeof(struct segment_command), &cmdsize32, &nsects32, \
				LC_SEGMENT };
		nlist_funk = (t_nlist_funk){ sizeof(struct nlist) };
	}
}

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

static void	nm_print()

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

bool		nm_agent(void)
{
	uint32_t		ncmds;
	t_mach_header	*ptr_header;

	if (!(ptr_header = get_safe(0, hdr_funk.size_of, IN_WHOLE)))
		return (log_error(ERR_FILE, "macho header fetch failed", FROM));
	if (!push_bounds(hdr_funk.size_of, hdr_funk.sizeofcmds(ptr_header)))
		return (log_error(ERR_THROW, "failed to set command bounds", FROM));
	ncmds = hdr_funk.ncmds(ptr_header);
	if (!iterate_load_commands(ncmds, seg_funk.type_of, &manage_segment))
		return (log_error(ERR_THROW, "failed to iterate over segment commands", FROM));
	if (!iterate_load_commands(ncmds, LC_SYMTAB, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtab commands", FROM));
	pop_bounds();
	return (true);
}

int			main(int argc, char **argv)
{
	if (argc < 2)
	{
		if (!extract_macho(DEFAULT_TARGET, &nm_agent, &nm_funk))
			return (EXIT_FAILURE);
	}
	while (*++argv)
	{
		if (**argv == '-')
		{
			//if (!nm_set_flag(*argv))
				return (EXIT_FAILURE);
		}
		else
		{
			ft_putchar('\n');
			ft_putstr(*argv);
			ft_putstr(":\n");
			if (!extract_macho(*argv, &nm_agent, &nm_funk))
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
