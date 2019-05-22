/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/22 18:22:37 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

// show usage in case of invalid flag or input

bool	nm_set_flag(char const *flag)
{
	if (ft_strlen(flag) >= 2)
		; //return (ft_log_error(ERR_FILE, "missing magic number", __func__)); ERR_FLAG "invalid or unknown flag"
	return (false);
}



// static bool is_64_global_static = false;

bool	iterate_segments(uint32_t target)
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
		return (log_error_false(ERR_FILE, "header fetch failed", __func__));
	if (!(command = get_safe(offset, sizeof(*command))))
			return (log_error(ERR_FILE, "load command fetch failed", __func__));
	ncmds = ft_swap32(header->ncmds);
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

bool	iterate_sections(size_t offset, char const *sectname_target,
	char const *segname_target)
{
	struct segment_command	*segment;
	struct section			*section;
	uint32_t				nsects;

	if (!(segment = get_safe(offset, (g_is_64) ? sizeof(*segment))))
		return (log_error(ERR_FILE, "segment command fetch failed", __func__));
	offset += sizeof(*segment);
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

bool	nm_agent()
{
	//
	if (!iterate_segments(LC_SYMTAB)) // , fct_ptr
		return (log_error(ERR_THROW, "", __func__));
	if (!iterate_sections())
	return (true);
}

static bool	inspect_magic_number(uint32_t magic)
{
	if (magic != MH_MAGIC && magic != MH_CIGAM && magic != MH_MAGIC_64
		&& magic != MH_CIGAM_64 && magic != FAT_MAGIC && magic != FAT_CIGAM
		&& magic != FAT_MAGIC_64 && magic != FAT_CIGAM_64)
		return (ft_log_error(ERR_FILE, "wrong magic number", __func__));
	set_endianness(magic == MH_CIGAM || magic == MH_CIGAM_64
		|| magic == FAT_CIGAM || magic == FAT_CIGAM_64);
	g_is_64 = (magic == MH_MAGIC_64 || magic == MH_CIGAM_64
		|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64);
	return (true);
}

// move this to common file
bool	inspect_macho(char const *filename, t_inspector agent)
{
	size_t		map_size;
	uint32_t	*magic;

	if (!(magic = get_safe(0, sizeof(*magic))))
		return (ft_log_error_null(ERR_FILE, "missing magic number", __func__));
	if (!inspect_magic_number(magic))
		return (ft_log_error(ERR_THROW, NULL, __func__));
	if (magic == FAT_MAGIC || magic == FAT_CIGAM || magic == FAT_MAGIC_64
		|| magic == FAT_CIGAM_64)
		;//agent()
	else
		;//agent()
	return (true);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		if (!load_file(DEFAULT_TARGET))
			return (EXIT_FAILURE);
		// extract_macho(&nm_agent);
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
