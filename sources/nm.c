/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 20:41:52 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// show usage in case of invalid flag or input

/*
bool	nm_set_flag(char const *flag)
{
	if (ft_strlen(flag) >= 2)
		; //return (ft_log_error(ERR_FILE, "missing magic number", __func__)); ERR_FLAG "invalid or unknown flag"
	return (false);
}
*/

bool	manage_segment(size_t offset)
{
	uint32_t			cmdsize;
	t_segment_command	*segment_cmd;

	if (!(segment_cmd = get_safe(offset, mode.sizeof_seg_cmd)))
		return (log_error(ERR_FILE, "segment command fetch failed", FROM));
	cmdsize = mode.get_cmdsize(segment_cmd);
	if (cmdsize < mode.sizeof_seg_cmd)
		return (log_error(ERR_FILE, "field cmdsize of segment command is invalid", FROM));
	if (!push_bounds(get_current_offset() + offset + mode.sizeof_seg_cmd, \
		cmdsize - mode.sizeof_seg_cmd))
		return (log_error(ERR_THROW, "failed to push bounds", FROM));
	if (!iterate_sections(mode.get_ncmds(segment_cmd), NULL, NULL, &machin))
		return (log_error(ERR_THROW, "failed to iterate over sections", FROM));
	pop_bounds();
	return (true);
}

bool	manage_symtab()
{
	return (true);
}

bool	nm_agent(void)
{
	t_mach_header	*header;

	if (!(header = get_safe(0, g_unit.sizeof_mach_header)))
		return (log_error(ERR_FILE, "macho header fetch failed", FROM));
	if (!push_bounds(g_unit.sizeof_mach_header, g_unit.get_sizeofcmds(header)))
		return (log_error(ERR_THROW, "failed to set command bounds", FROM));
	if (!iterate_load_commands(mode.get_ncmds(header), \
		(g_is_64) ? LC_SEGMENT_64 : LC_SEGMENT, &manage_segment)) // -> to g_unit !
		return (log_error(ERR_THROW, "failed to iterate over segment commands", FROM));
	if (!iterate_load_commands(LC_SYMTAB, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtab commands", FROM));
	pop_bounds();
	return (true);
}

// ce main est immonde
int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		if (!load_file(DEFAULT_TARGET))
			return (EXIT_FAILURE);
		extract_macho(&nm_agent);
		if (!unload_file())
			return (EXIT_FAILURE);
	}
	while (*++argv)
	{
		if (**argv == '-')
		{
			if (!nm_set_flag(*argv))
				return (-1);
		}
		else
		{
			ft_putchar('\n');
			ft_putstr(*argv);
			ft_putstr(":\n");
			if (!load_file(*argv)) {
				extract_macho(*argv, &nm_agent);
				unload_file();
			}
		}
	}
	return (0);
}
