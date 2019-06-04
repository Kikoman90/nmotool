/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch_funk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:19:56 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 18:34:57 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

uint64_t	offset32(t_fat_arch const *fata)
{
	return ((uint64_t)swap32(fata->fat_arch32.offset));
}

uint64_t	offset64(t_fat_arch const *fata)
{
	return (swap64(fata->fat_arch64.offset));
}

uint64_t	size32(t_fat_arch const *fata)
{
	return ((uint64_t)swap32(fata->fat_arch32.size));
}

uint64_t	size64(t_fat_arch const *fata)
{
	return (swap64(fata->fat_arch64.size));
}
