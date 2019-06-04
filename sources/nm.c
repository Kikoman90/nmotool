/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 17:05:55 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// flag handling
// show usage in case of invalid flag or input

static bool	manage_segment(size_t offset, t_funk funk)
{
	uint32_t				cmdsize;
	t_segment_funk			segment_funk;
	t_segment_command const	*ptr_segment_cmd;

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

static bool	manage_symtab(size_t offset, t_funk funk)
{
	uint32_t					nsyms;
	t_nlist_funk				nlist_funk;
	t_nlist const				*ptr_nlist;
	struct symtab_command const	*ptr_symtab;
	// t_symbol_info			*symbols;
	
	nlist_funk = funk.nlist();
	if (!(ptr_symtab = get_safe(offset, sizeof(*ptr_symtab), BT_TOP)))
		return (log_error(ERR_FILE, "failed to get symtab command", FROM));
	nsyms = ptr_symtab->nsyms;
	if (!(ptr_nlist = get_safe(ptr_symtab->symoff, \
		nsyms * nlist_funk.size_of, BT_MACHO))) // symoff relative to MACHO or to FILE ??
		return (log_error(ERR_FILE, "failed to get nlist array", FROM));
	// string table : safe, bounds...
	printf("nsyms = %ui\n", nsyms);
	//
	while (nsyms--)
	{
		/*symbols[ = extract_nlist_symbol_info(nlist_funk.n_type(ptr_nlist), \
			nlist_funk.n_sect(ptr_nlist), nlist_funk.n_desc(ptr_nlist), \
			nlist_funk.n_value(ptr_nlist));
		symbol.max_string_size
		symbol.string
		symbol.*/
		ptr_nlist = (t_nlist*)((char*)ptr_nlist + nlist_funk.size_of);
	}
	//nmprint(symbols, ptr_symtab->stroff + ptr_symtab->strsize);
	return (true);
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
	if (!iterate_load_commands(ncmds, funk.segment().type_of, funk, \
		&manage_segment))
		return (log_error(ERR_THROW, "failed to iterate over segments", FROM));
	if (!iterate_load_commands(ncmds, LC_SYMTAB, funk, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtabs", FROM));
	pop_bounds(BT_TOP);
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
