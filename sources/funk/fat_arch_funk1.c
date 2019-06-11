/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch_funk1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:19:56 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/11 19:57:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

uint64_t		offset32(t_fat_arch const *fata)
{
	return ((uint64_t)swap32(fata->fat_arch32.offset));
}

uint64_t		size32(t_fat_arch const *fata)
{
	return ((uint64_t)swap32(fata->fat_arch32.size));
}

cpu_type_t		cputype32(t_fat_arch const *fata)
{
	return ((cpu_type_t)signed_swap32((int32_t)fata->fat_arch32.cputype));
}

cpu_subtype_t	cpusubtype32(t_fat_arch const *fata)
{
	return ((cpu_subtype_t)signed_swap32((int32_t)fata->fat_arch32.cpusubtype));
}
