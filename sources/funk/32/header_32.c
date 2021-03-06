/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:27:43 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 14:51:05 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	ncmds(t_mach_header const *ptr_header)
{
	return (swap32(ptr_header->header_32.ncmds));
}

static uint32_t	sizeofcmds(t_mach_header const *ptr_header)
{
	return (swap32(ptr_header->header_32.sizeofcmds));
}

t_header_funk	header_funk_32(void)
{
	return ((t_header_funk){ sizeof(struct mach_header), &ncmds, &sizeofcmds });
}
