/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   machop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:56:51 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:10:14 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

bool		iterate_load_commands(uint32_t ncmds, uint32_t target, \
	t_funk funk, t_command_op opera)
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

bool		iterate_sections(uint32_t nsects, char const *names[2], \
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

static bool	manage_fat(size_t offset, size_t size, uint32_t magic, \
	t_conductor ctor)
{
	t_fat_arch_funk	fat_arch_funk;

	set_endianness(MAGIC_IS_CIGAM(magic));
	fat_arch_funk = (MAGIC_IS_64(magic)) ? \
		(t_fat_arch_funk){ sizeof(struct fat_arch_64), &offset64, &size64 } : \
		(t_fat_arch_funk){ sizeof(struct fat_arch), &offset32, &size32 };
	// nfat_arch blabla
	
	(void)offset;
	(void)size;
	(void)ctor;
	return (true);
}

static bool	manage_macho(size_t offset, size_t size, uint32_t magic, \
	t_conductor ctor)
{
	bool	ret;
	t_funk	funk;

	if (!push_bounds(offset, size, BT_MACHO))
		return (log_error(ERR_THROW, "failed to set macho bounds", FROM));
	set_endianness(MAGIC_IS_CIGAM(magic));
	funk = (MAGIC_IS_64(magic)) ? \
		(t_funk){ &header64, &segment64, &section64, &nlist64 } : \
		(t_funk){ &header32, &segment32, &section32, &nlist32 };
	ret = ctor(funk);
	pop_bounds(BT_MACHO);
	return (ret);
}

bool		machopera(char const *filepath, t_conductor ctor)
{
	bool			ret;
	size_t			filesize;
	uint32_t const	*ptr_magic;

	ret = true;
	if (!load_file(filepath, &filesize))
		ret = log_error(ERR_THROW, "could not load file", FROM);
	else if (!(ptr_magic = get_safe(0, sizeof(*ptr_magic), BT_FILE)))
		ret = log_error(ERR_THROW, "failed to get magic number", FROM);
	else if (*ptr_magic == 9090) //ARMAG
		ret = false;
	else if (*ptr_magic == FAT_MAGIC || *ptr_magic == FAT_MAGIC_64 \
		|| *ptr_magic == FAT_CIGAM || *ptr_magic == FAT_CIGAM_64)
		ret = manage_fat(0, filesize, *ptr_magic, ctor);
	else if (*ptr_magic == MH_MAGIC || *ptr_magic == MH_MAGIC_64 \
		|| *ptr_magic == MH_CIGAM || *ptr_magic == MH_CIGAM_64)
		ret = manage_macho(0, filesize, *ptr_magic, ctor);
	else
		ret = log_error(ERR_FILE, "invalid/unsupported architecture", FROM);
	return ((!unload_file()) ? \
		log_error(ERR_THROW, "could not unload file", FROM) : ret);
}
