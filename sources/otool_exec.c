/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 11:19:03 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 16:04:02 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

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
		(char const *[2]){ "__TEXT", "__text" }, funk.section(), \
		&print_section_content))
		return (log_error(ERR_THROW, "failed to iterate over sections", FROM));
	pop_bounds(BT_TOP);
	return (true);
}

bool		otool_conductor(t_funk funk)
{
	uint32_t			ncmds;
	t_header_funk		header_funk;
	t_mach_header const	*ptr_header;

	set_otool_print_padding(funk.print_padding);
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
	pop_bounds(BT_TOP);
	return (true);
}
