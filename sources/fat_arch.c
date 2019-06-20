/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 20:11:02 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 17:57:44 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static bool g_all_arch = false;

void		toggle_fat_show_all_arch(void)
{
	g_all_arch = !g_all_arch;
}

static void	print_arch(char const *arch_name)
{
	static bool	first_arch = true;

	if (first_arch)
		first_arch = false;
	else
		ft_putchar('\n');
	ft_putstr("(for architecture ");
	ft_putstr(arch_name);
	ft_putendl("):");
}

static bool	arch_is_valid(t_fat_arch const *ptr_fat_arch, \
	t_fat_arch_funk arch_funk, uint32_t *ptr_valid_magic, bool found_valid)
{
	uint32_t			*ptr_magic;
	NXArchInfo const	*ptr_arch_info;

	if (!(ptr_magic = get_safe(arch_funk.offset(ptr_fat_arch), \
		arch_funk.size(ptr_fat_arch), BT_FILE)))
		return (log_error(ERR_THROW, "failed to get magic number", FROM));
	if (!(ptr_arch_info = NXGetArchInfoFromCpuType(\
		arch_funk.cputype(ptr_fat_arch), arch_funk.cpusubtype(ptr_fat_arch))))
		return (log_error(ERR_THROW, "failed to get architecture info", FROM));
	if (arch_funk.cputype(ptr_fat_arch) == CPU_ARCH \
		|| ((!found_valid || g_all_arch) && (*ptr_magic == MH_MAGIC_64 \
		|| *ptr_magic == MH_CIGAM_64 || *ptr_magic == MH_MAGIC \
		|| *ptr_magic == MH_CIGAM)))
	{
		if (g_all_arch)
			print_arch(ptr_arch_info->name);
		*ptr_valid_magic = *ptr_magic;
		return (true);
	}
	return (false);
}

static bool	extract_arch(uint32_t nfat_arch, t_fat_arch_funk arch_funk, \
	bool endian_swap, t_conductor ctor)
{
	uint32_t			valid_magic;
	t_fat_arch const	*ptr_valid;
	t_fat_arch const	*ptr_fat_arch;

	if (!(ptr_fat_arch = get_safe(sizeof(struct fat_header), \
		nfat_arch * arch_funk.size_of, BT_FILE)))
		return (log_error(ERR_THROW, "failed to get fat_arch array", FROM));
	ptr_valid = NULL;
	while (nfat_arch--)
	{
		set_endianness(endian_swap);
		if (arch_is_valid(ptr_fat_arch, arch_funk, &valid_magic, (ptr_valid)))
		{
			ptr_valid = ptr_fat_arch;
			if (g_all_arch)
				manage_macho(arch_funk.offset(ptr_valid), \
					arch_funk.size(ptr_valid), valid_magic, ctor);
		}
		ptr_fat_arch = (t_fat_arch*)((char*)ptr_fat_arch + arch_funk.size_of);
	}
	if (!ptr_valid)
		return (log_error(ERR_THROW, "no known architectures found", FROM));
	return ((!g_all_arch) ? manage_macho(arch_funk.offset(ptr_valid), \
		arch_funk.size(ptr_valid), valid_magic, ctor) : true);
}

bool		manage_fat(uint32_t magic, t_conductor ctor)
{
	bool					endian_swap;
	uint32_t				nfat_arch;
	t_fat_arch_funk			arch_funk;
	struct fat_header const	*ptr_header;

	set_endianness(endian_swap = (magic == MH_CIGAM || magic == MH_CIGAM_64 \
		|| magic == FAT_CIGAM || magic == FAT_CIGAM_64));
	if (!(ptr_header = get_safe(0, sizeof(*ptr_header), BT_FILE)))
		return (log_error(ERR_THROW, "failed to get fat header", FROM));
	nfat_arch = swap32(ptr_header->nfat_arch);
	arch_funk = (magic == MH_MAGIC_64 || magic == MH_CIGAM_64 \
		|| magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64) ? \
		fat_arch_funk_64() : fat_arch_funk_32();
	return (extract_arch(nfat_arch, arch_funk, endian_swap, ctor));
}
