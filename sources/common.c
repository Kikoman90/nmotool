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

bool		iterate_load_commands(uint32_t target, t_lc_manager funk)
{
	static const size_t header_sizes[2] = {
		sizeof(struct mach_header),
		sizeof(struct mach_header_64)
	};
	struct mach_header	*header;
	struct load_command	*command;
	uint32_t			ncmds;
	size_t				offset;

	offset = header_sizes[g_is_64];
	if (!(header = get_safe(0, offset)))
		return (log_error(ERR_FILE, "header fetch failed", __func__));
	if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_FILE, "load command fetch failed", __func__));
	ncmds = swap32(header->ncmds);
	while (ncmds--)
	{
		if (swap32(command->cmd) == target && offset)// && )
			return (log_error(ERR_THROW, NULL, __func__));
		offset += swap32(command->cmdsize);
		if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_FILE, "load command fetch failed", __func__));
	}
	return (true);
}

bool		iterate_sections(size_t offset, char const *sectname_target, \
				char const *segname_target, t_section_manager funk)
{
	//struct segment_command	*segment;
	void					*ptr_segment;
	struct section			*section;
	uint64_t				nsects;

	//if (!(segment = get_safe(offset, (g_is_64) ? sizeof(*segment) : sizeof(64lol)))
	//	return (log_error(ERR_FILE, "segment command fetch failed", __func__));
	//offset += sizeof(*segment);
	if (!(section = get_safe(offset, sizeof(*section))))
		return (log_error(ERR_FILE, "section fetch failed", __func__));
	nsects = swap32(segment->nsects);
	while (nsects--)
	{
		if ((!sectname_target || !ft_strcmp(sectname_target, section->sectname))
			&& (!segname_target || !ft_strcmp(segname_target, section->segname))
			&& func(offset))
			return (log_error(ERR_THROW, NULL, __func__));
		offset += sizeof(*section);
		if (!(section = get_safe(offset, sizeof(*section))))
			return (log_error(ERR_FILE, "section fetch failed", __func__));
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
		return (log_error(ERR_FILE, "failed to get magic number", FROM, NULL));
	inspect_magic_number(*magic);

	if (*magic == AR_MAGIC || *magic == AR_CIGAM)
		ret = false; // manage_archive(agent);
	else if (*magic == FAT_MAGIC || *magic == FAT_CIGAM \
		|| *magic == FAT_MAGIC_64 || *magic == FAT_CIGAM_64)
		ret = false; // manage_fat(agent);
	else if (*magic == MH_MAGIC || *magic == MH_CIGAM \
		|| *magic == MH_MAGIC_64 || *magic == MH_CIGAM_64)
		ret = agent();
	else
		ret = log_error(ERR_THROW, "invalid/unsupported magic", FROM, NULL);
	// unload file ? here ?
	return (ret);
}
