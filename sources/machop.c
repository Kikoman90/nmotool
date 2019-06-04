/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:56:51 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 18:50:11 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool	iterate_load_commands(uint32_t ncmds, uint32_t target, t_funk funk, \
	t_command_op opera)
{
	size_t						offset;
	struct load_command const	*command;

	offset = 0;
	while (ncmds--)
	{
		if (!(command = get_safe(offset, sizeof(*command), BT_TOP)))
			return (log_error(ERR_THROW, "failed to get command", FROM));
		if (swap32(command->cmd) == target && !opera(offset, funk))
			return (log_error(ERR_THROW, "command operation failed", FROM));
		offset += swap32(command->cmdsize);
	}
	return (true);
}

bool	iterate_sections(uint32_t nsects, char const *names[2], \
	t_section_funk funk, t_section_op opera)
{
	uint32_t		i;
	char			sectname[16];
	char			segname[16];
	t_section const	*ptr_section;

	i = 0;
	if (!(ptr_section = get_safe(0, nsects * funk.size_of, BT_TOP)))
		return (log_error(ERR_THROW, "failed to get section", FROM));
	while (i < nsects)
	{
		funk.get_segname(ptr_section, segname);
		funk.get_sectname(ptr_section, sectname);
		if ((!names[0] || !ft_strcmp(names[0], segname)) \
			&& (!names[1] || !ft_strcmp(names[1], sectname)))
			opera(i * funk.size_of);
		ptr_section = (t_section*)((char*)ptr_section + funk.size_of);
		i++;
	}
	return (true);
}

/*
** funk = ((length = MAGIC_IS_64(*ptr_magic))) ?
*/
bool	machopera(size_t dist, size_t length, t_conductor ctor)
{
	bool			ret;
	uint32_t const	*ptr_magic;
	t_funk			funk;

	if (!push_bounds(dist, length, BT_MACHO))
		return (log_error(ERR_THROW, "failed to set macho bounds", FROM));
	if (!(ptr_magic = get_safe(0, sizeof(*ptr_magic), BT_MACHO)))
		ret = log_error(ERR_THROW, "failed to get magic number", FROM);
	else if ((ret = true))
	{
		if ((dist = MAGIC_IS_CIGAM(*ptr_magic)))
			set_endianness(true);
		length = MAGIC_IS_64(*ptr_magic);
		funk = (length) ? \
			(t_funk){ &fat64, &header64, &segment64, &section64, &nlist64 } : \
			(t_funk){ &fat32, &header32, &segment32, &section32, &nlist32 };
		if (*ptr_magic == ARMAG)
			ret = false;
		else if (*ptr_magic == (dist ? FAT_CIGAM_(length) : FAT_MAGIC_(length)))
			ret = false;
		else if (*ptr_magic == (dist ? MH_CIGAM_(length) : MH_MAGIC_(length)))
			ret = ctor(funk);
		else
			ret = log_error(ERR_THROW, "invalid/unsupported architecture", FROM);
	}
	pop_bounds(BT_MACHO);
	return (ret);
}

bool	play_macho(char const *filepath, t_conductor ctor)
{
	bool	ret;
	size_t	filesize;

	ret = true;
	if (!load_file(filepath, &filesize))
		ret = log_error(ERR_THROW, "could not load file", FROM);
	else if (!machopera(0, filesize, ctor))
		ret = log_error(ERR_THROW, "could not extract macho", FROM);
	return ((!unload_file()) ? \
		log_error(ERR_THROW, "could not unload file", FROM) : ret);
}
