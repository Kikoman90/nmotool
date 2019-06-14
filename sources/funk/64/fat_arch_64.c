/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:50:16 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 14:52:11 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint64_t			offset(t_fat_arch const *ptr_fat_arch)
{
	return (swap64(ptr_fat_arch->fat_arch_64.offset));
}

static uint64_t			size(t_fat_arch const *ptr_fat_arch)
{
	return (swap64(ptr_fat_arch->fat_arch_64.size));
}

static cpu_type_t		cputype(t_fat_arch const *ptr_fat_arch)
{
	return ((cpu_type_t)\
		signed_swap32((int32_t)ptr_fat_arch->fat_arch_64.cputype));
}

static cpu_subtype_t	cpusubtype(t_fat_arch const *ptr_fat_arch)
{
	return ((cpu_subtype_t)\
		signed_swap32((int32_t)ptr_fat_arch->fat_arch_64.cpusubtype));
}

t_fat_arch_funk			fat_arch_funk_64(void)
{
	return ((t_fat_arch_funk){ sizeof(struct fat_arch_64), &offset, &size, \
		&cputype, &cpusubtype });
}
