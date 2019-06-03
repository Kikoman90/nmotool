// 42 header //

#include "common.h"

bool	iterate_load_commands(uint32_t ncmds, uint32_t target, \
	t_command_op opera)
{
	size_t				offset;
	struct load_command	*command;

	offset = 0;
	while (ncmds--)
	{
		if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_THROW, "failed to get command", FROM));
		if (swap32(command->cmd) == target && !opera(offset))
			return (log_error(ERR_THROW, "command operation failed", FROM));
		offset += swap32(command->cmdsize);
	}
	return (true);
}

bool	iterate_sections(uint32_t nsects, char const *names[2], \
	t_section_funk funk, t_section_op opera)
{
	uint32_t	i;
	t_section	*ptr_section;

	i = 0;
	if (!(ptr_section = get_safe(0, nsects * funk.size_of)))
		return (log_error(ERR_THROW, "failed to get section", FROM));
	while (i < nsects)
	{
		if ((!names[0] || !ft_strcmp(names[0], funk.segname(ptr_section))) \
			&& (!names[1] || !ft_strcmp(names[1], funk.sectname(ptr_section))))
			opera(i * funk.size_of);
		ptr_section = (t_section*)((char*)ptr_section + funk.size_of);
		i++;
	}
	return (true);
}

bool	machopera(size_t dist, size_t length, t_conductor ctor)
{
	bool			ret;
	uint32_t const	*ptr_magic;
	t_funk			funk;

	if (!push_bounds(dist, length, MACHO))
		return (log_error(ERR_THROW, "failed to set macho bounds", FROM));
	if (!(ptr_magic = get_safe(0, sizeof(*ptr_magic), MACHO)))
		ret = log_error(ERR_THROW, "failed to get magic number", FROM);
	else if ((ret = true))
	{
		if ((dist = MAGIC_IS_CIGAM(*ptr_magic)))
			set_endianness(true);
		funk = ((length = MAGIC_IS_64(*ptr_magic))) ? \
			(t_funk){ &header64, &segment64, &section64, &nlist64, &fat64 } : \
			(t_funk){ &header32, &segment32, &section32, &nlist32, &fat32 };
		if (*ptr_magic == ARMAG)
			ret = false; // manage_archive(ctor, funk);
		else if (*ptr_magic == (dist ? FAT_CIGAM(length) : FAT_MAGIC(length)))
			ret = false; // manage_fat(ctor, funk);
		else if (*ptr_magic == (dist ? MH_CIGAM(length) : MH_MAGIC(length)))
			ret = ctor(funk);
		else
			ret = log_error(ERR_THROW, "invalid/unsupported architecture", FROM);
	}
	pop_bounds(MACHO);
	return (ret);
}

bool	play_macho(char const *filepath, t_conductor ctor)
{
	bool	ret;

	ret = true;
	if (!load file(filepath))
		ret = log_error(ERR_THROW, "could not load file", FROM);
	else if (!machopera(ctor))
		ret = log_error(ERR_THROW, "could not extract macho", FROM);
	return ((!unload_file()) ? \
		log_error(ERR_THROW, "could not unload file", FROM) : ret);
}
