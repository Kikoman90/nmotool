/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch_funk2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 16:50:16 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/11 19:57:17 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

uint64_t		offset64(t_fat_arch const *fata)
{
	return (swap64(fata->fat_arch64.offset));
}

uint64_t		size64(t_fat_arch const *fata)
{
	return (swap64(fata->fat_arch64.size));
}

cpu_type_t		cputype64(t_fat_arch const *fata)
{
	return ((cpu_type_t)signed_swap32((int32_t)fata->fat_arch64.cputype));
}

cpu_subtype_t	cpusubtype64(t_fat_arch const *fata)
{
	return ((cpu_subtype_t)signed_swap32((int32_t)fata->fat_arch64.cpusubtype));
}
