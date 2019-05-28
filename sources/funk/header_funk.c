/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:27:43 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/28 16:23:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint32_t	ncmds32(t_mach_header *ptr_hdr)
{
	return (swap32(ptr_hdr->mach_hdr32.ncmds));
}

uint32_t	ncmds64(t_mach_header *ptr_hdr)
{
	return (swap32(ptr_hdr->mach_hdr64.ncmds));
}

uint32_t	sizeofcmds32(t_mach_header *ptr_hdr)
{
	return (swap32(ptr_hdr->mach_hdr32.sizeofcmds));
}

uint32_t	sizeofcmds64(t_mach_header *ptr_hdr)
{
	return (swap32(ptr_hdr->mach_hdr64.sizeofcmds));
}
