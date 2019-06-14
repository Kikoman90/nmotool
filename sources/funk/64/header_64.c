/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:59:31 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 14:52:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	ncmds(t_mach_header const *ptr_header)
{
	return (swap32(ptr_header->header_64.ncmds));
}

static uint32_t	sizeofcmds(t_mach_header const *ptr_header)
{
	return (swap32(ptr_header->header_64.sizeofcmds));
}

t_header_funk	header_funk_64(void)
{
	return ((t_header_funk)\
		{ sizeof(struct mach_header_64), &ncmds, &sizeofcmds });
}
