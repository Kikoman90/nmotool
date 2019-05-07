/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/03/14 16:54:41 by fsidler          ###   ########.fr       */
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

static bool is_64_global_static = false;

void	*nm_agent( bool is_64)
{
	static const size_t header_sizes[2] = {
		sizeof(struct mach_header),
		sizeof(struct mach_header_64)
	};
	struct mach_header	*header;

	if (!(header = (struct mach_header*)get_safe(0, header_sizes[is_64])))
		; //return (ft_log_error_false(ERR_HEADER, "header fetch failed", __func__));
	

}

bool	inspect_magic_number(uint32_t magic_number)
{
	if (magic_number == MH_CIGAM)
		agent(false, true);
	else if (magic_number & MH_CIGAM_64)
	{
		file_is_little_endian();
		file_is_64();
	}
	else if (magic_number == MH_MAGIC)
}

void	*inspect_macho(char const *filename, t_inspector agent)
{
	void		*ptr;
	size_t		map_size;
	uint32_t	*magic_number;

	if (!(ptr = ft_file_map(filename, &map_size)))
		return (NULL);
	init_safe_pointer(ptr, map_size);
	if (!(magic_number = get_safe(0, sizeof(*magic_number))))
		return (ft_log_error_null(ERR_FILE, "missing magic number", __func__));
	if (magic_number == MH_MAGIC)

	
	
	
	
	
	
	
	inspect_magic_number(magic_number);
	check_endianness(*magic_number == MH_CIGAM || \
		*magic_number == MH_CIGAM_64 || *magic_number == FAT_CIGAM || \
		*magic_number == FAT_CIGAM_64); // || magic_number == ARCHIVE_CIGAM)
	// create ARCHIVE magic numbers ??
	// check_endianness suivi de tous ces ifs est rebarbatif
	/**/

	if (magic_number == MH_MAGIC || magic_number == MH_CIGAM)
		agent(false);
	else if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
		agent(true);

	/**/
	/*
	else if (magic_number == FAT_MAGIC || magic_number == FAT_CIGAM)
		extract_fat(ptr, false);
	else if (magic_number == FAT_MAGIC_64 || magic_number == FAT_CIGAM_64)
		extract_fat(ptr, true); // bool is_64 ?
	else if (magic_number == ARCHIVE_MAGIC || magic_number == ARCHIVE_CIGAM)
		extract_archive(ptr); */
	ft_file_unmap(ptr, map_size, NULL);
	return (NULL);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		extract_macho(DEFAULT_TARGET, &nm_agent);
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
			extract_macho(*argv, &nm_agent);
		}
	}
	return (0);
}
