/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:56:51 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 15:23:36 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	iterate_load_commands(uint32_t ncmds, uint32_t target, t_funk funk, \
	t_command_op opera)
{
	size_t						offset;
	size_t						match_count;
	struct load_command const	*command;

	offset = 0;
	match_count = 0;
	while (ncmds--)
	{
		if (!(command = get_safe(offset, sizeof(*command), BT_TOP)))
			return (log_error(ERR_THROW, "failed to get command", FROM));
		if (swap32(command->cmd) == target)
		{
			match_count++;
			if (target == LC_SYMTAB && match_count != 1)
				return (log_error(ERR_FILE, "too many symtab commands", FROM));
			if (!opera(offset, funk))
				return (log_error(ERR_THROW, "command operation failed", FROM));
		}
		offset += swap32(command->cmdsize);
	}
	return (true);
}

bool	iterate_sections(uint32_t nsects, char const *names[2], \
	t_section_funk section_funk, t_section_op opera)
{
	uint32_t		i;
	char			sectname[16];
	char			segname[16];
	t_section const	*ptr_section;

	i = 0;
	if (!(ptr_section = get_safe(0, nsects * section_funk.size_of, BT_TOP)))
		return (log_error(ERR_THROW, "failed to get section", FROM));
	while (i < nsects)
	{
		section_funk.get_segname(ptr_section, segname);
		section_funk.get_sectname(ptr_section, sectname);
		if ((!names[0] || !ft_strcmp(names[0], segname)) \
			&& (!names[1] || !ft_strcmp(names[1], sectname)) \
			&& !opera(ptr_section, section_funk))
			return (log_error(ERR_THROW, "section operation failed", FROM));
		ptr_section = (t_section*)((char*)ptr_section + section_funk.size_of);
		i++;
	}
	return (true);
}

bool	manage_macho(size_t offset, size_t size, uint32_t magic, \
	t_conductor ctor)
{
	t_funk	funk;

	if (!push_bounds(offset, size, BT_MACHO))
		return (log_error(ERR_THROW, "failed to set macho bounds", FROM));
	set_endianness(MAGIC_IS_CIGAM(magic));
	funk = set_funk(MAGIC_IS_64(magic));
	if (!ctor(funk))
	{
		pop_bounds(BT_MACHO);
		return (log_error(ERR_THROW, "macho operation failed", FROM));
	}
	pop_bounds(BT_MACHO);
	return (true);
}

bool	machopera(char const *filepath, t_conductor ctor)
{
	bool			ret;
	size_t			filesize;
	uint32_t const	*ptr_magic;

	if (!(ret = load_file(filepath, &filesize)))
		ret = log_error(ERR_THROW, "could not load file", FROM);
	else if (!(ptr_magic = get_safe(0, sizeof(*ptr_magic), BT_FILE)))
		ret = log_error(ERR_THROW, "failed to get magic number", FROM);
	else if (get_safe(0, SARMAG, BT_FILE) \
		&& !ft_strcmp(get_safe(0, SARMAG, BT_FILE), ARMAG))
		ret = log_error(ERR_USAGE, "archive support not yet implemented", FROM);
	else if (*ptr_magic == FAT_MAGIC || *ptr_magic == FAT_MAGIC_64 \
		|| *ptr_magic == FAT_CIGAM || *ptr_magic == FAT_CIGAM_64)
		ret = manage_fat(*ptr_magic, ctor);
	else if (*ptr_magic == MH_MAGIC || *ptr_magic == MH_MAGIC_64 \
		|| *ptr_magic == MH_CIGAM || *ptr_magic == MH_CIGAM_64)
		ret = manage_macho(0, filesize, *ptr_magic, ctor);
	else
		ret = log_error(ERR_FILE, "invalid/unsupported architecture", FROM);
	return ((!unload_file()) ? \
		log_error(ERR_THROW, "could not unload file", FROM) : ret);
}
