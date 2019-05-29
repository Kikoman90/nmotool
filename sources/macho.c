/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 12:59:56 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 18:18:01 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static t_section_funk sect_funk;

void		set_section_funk(bool is_64)
{
	if (is_64)
		sect_funk = (t_section_funk)\
			{ sizeof(struct section_64), &sectname64, &segname64 };
	else
		sect_funk = (t_section_funk)\
			{ sizeof(struct section), &sectname32, &segname32 };
}

bool		iterate_load_commands(uint32_t ncmds, uint32_t target, \
				t_lc_manager mana)
{
	size_t				offset;
	struct load_command	*command;

	offset = 0;
	while (ncmds--)
	{
		if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_FILE, "load command fetch failed", FROM));
		if (swap32(command->cmd) == target && !mana(offset))
			return (log_error(ERR_THROW, "load command manager failed", FROM));
		offset += swap32(command->cmdsize);
	}
	return (true);
}

/*
if (!(ptr_section = get_safe(offset, sect_funk.size_of)))
	return (log_error(ERR_FILE, "section fetch failed", FROM));
offset += sect_funk.size_of;
*/

bool		iterate_sections(uint32_t nsects, char const *sectname_target, \
				char const *segname_target, t_section_manager mana)
{
	uint32_t	i;
	t_section	*ptr_section;

	i = 0;
	if (!(ptr_section = get_safe(0, nsects * sect_funk.size_of)))
		return (log_error(ERR_FILE, "sections fetch failed", FROM));
	while (i < nsects)
	{
		if ((!sectname_target || \
			!ft_strcmp(sectname_target, sect_funk.sectname(ptr_section))) \
			&& (!segname_target || \
			!ft_strcmp(segname_target, sect_funk.segname(ptr_section))))
			mana(i * sect_funk.size_of);
		//return (log_error(ERR_THROW, "section manager failed", FROM));
		ptr_section = (t_section*)((char*)ptr_section + sect_funk.size_of);
		i++;
	}
	return (true);
}

static bool	set_funky(uint32_t *ptr_magic, t_funk funk)
{
	bool	is_64;
	
	if (!(ptr_magic = get_safe(0, sizeof(*ptr_magic))))
		return (log_error(ERR_FILE, "failed to get magic number", FROM));
	set_endianness(*ptr_magic == MH_CIGAM || *ptr_magic == MH_CIGAM_64
		|| *ptr_magic == FAT_CIGAM || *ptr_magic == FAT_CIGAM_64);
	is_64 = (*ptr_magic == MH_MAGIC_64 || *ptr_magic == MH_CIGAM_64
		|| *ptr_magic == FAT_MAGIC_64 || *ptr_magic == FAT_CIGAM_64);
	funk(is_64);
	return (true);
}

bool		extract_macho(char const *filepath, t_agent agent, t_funk funk)
{
	bool		ret;
	uint32_t	*ptr_magic;

	if (!load_file(filepath)) //
		return (log_error(ERR_THROW, "could not load file", FROM)); //
	ptr_magic = NULL;
	if (!set_funky(ptr_magic, funk))
	{
		if (!unload_file()) //
			log_error(ERR_THROW, "could not unload file", FROM); //
		return (log_error(ERR_THROW, "macho settings could not be set", FROM));
	}
	if (*ptr_magic == *((uint32_t*)ARMAG))
		ret = false; // manage_archive(agent);
	else if (*ptr_magic == FAT_MAGIC || *ptr_magic == FAT_CIGAM \
		|| *ptr_magic == FAT_MAGIC_64 || *ptr_magic == FAT_CIGAM_64)
		ret = false; // manage_fat(agent);
	else if (*ptr_magic == MH_MAGIC || *ptr_magic == MH_CIGAM \
		|| *ptr_magic == MH_MAGIC_64 || *ptr_magic == MH_CIGAM_64)
		ret = agent();
	else
		ret = log_error(ERR_THROW, "invalid/unsupported magic", FROM);
	if (!unload_file()) //
			log_error(ERR_THROW, "could not unload file", FROM); //
	return (ret);
}
