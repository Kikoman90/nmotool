/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:59:56 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 20:44:42 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

// push_bounds/pop_bounds !

bool		iterate_load_commands(uint32_t ncmds, uint32_t target, t_lc_manager funk)
{
	size_t				offset;
	struct load_command	*command;

	offset = 0;
	while (ncmds--)
	{
		if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_FILE, "load command fetch failed", FROM));
		if (swap32(command->cmd) == target && !funk(offset, command->cmdsize))
			return (log_error(ERR_THROW, "load command manager failed", FROM));
		offset += swap32(command->cmdsize);
	}
	return (true);
}

bool		iterate_sections(uint32_t nsects, char const *sectname_target, \
				char const *segname_target, t_section_manager funk)
{
	t_section	*section;

	size_t			offset;
	size_t			section_struct_size;
	struct section	*section;

	offset = 0;
	while (nsects--)
	{
		if (!(section = get_safe(offset, mode.sizeof_sec)))
			return (log_error(ERR_FILE, "section fetch failed", FROM));
		if ((!sectname_target || !ft_strcmp(sectname_target, mode.get_sectname(section)))
			&& (!segname_target || !ft_strcmp(segname_target, mode.get_segname(section)))
			&& funk(offset))
			return (log_error(ERR_THROW, "section manager failed", FROM));
		offset += mode.sizeof_sec;
	}
	return (true);
}

static void	inspect_magic_number(uint32_t magic)
{
	set_endianness(magic == MH_CIGAM || magic == MH_CIGAM_64
		|| magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	g_is_64 = (magic == MH_MAGIC_64 || magic == MH_CIGAM_64
		|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64);
}

bool		extract_macho(t_agent agent)
{
	uint32_t	*magic;
	bool		ret;

	// load file ? here ?
	if (!(magic = get_safe(0, sizeof(*magic))))
		return (log_error(ERR_FILE, "failed to get magic number", FROM));
	inspect_magic_number(*magic);

	// set funk pointers ! 32/64

	if (*magic == AR_MAGIC || *magic == AR_CIGAM)
		ret = false; // manage_archive(agent);
	else if (*magic == FAT_MAGIC || *magic == FAT_CIGAM \
		|| *magic == FAT_MAGIC_64 || *magic == FAT_CIGAM_64)
		ret = false; // manage_fat(agent);
	else if (*magic == MH_MAGIC || *magic == MH_CIGAM \
		|| *magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		ret = agent();
	else
		ret = log_error(ERR_THROW, "invalid/unsupported magic", FROM);
	// unload file ? here ?
	return (ret);
}
