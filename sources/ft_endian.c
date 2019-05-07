/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:43:30 by fsidler           #+#    #+#             */
/*   Updated: 2019/03/11 17:16:42 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static bool	little_endian = false;

void		check_endianness(bool is_little_endian)
{
	little_endian = is_little_endian;
}

uint16_t    ft_swap16(uint16_t x)
{
	return (little_endian ? x >> 8 | x << 8 : x);
}

uint32_t	ft_swap32(uint32_t x)
{
	return (little_endian ? \
		x >> 24 | (x & 0x00ff0000) >> 8 | (x & 0x0000ff00) << 8 | x << 24 : x);
}

uint64_t	ft_swap64(uint64_t x)
{
	return (little_endian ? x >> 56 | (x & 0x00ff000000000000ULL) >> 40 |\
		(x & 0x0000ff0000000000ULL) >> 24 | (x & 0x000000ff00000000ULL) >>  8 |\
		(x & 0x00000000ff000000ULL) <<  8 | (x & 0x0000000000ff0000ULL) << 24 |\
		(x & 0x000000000000ff00ULL) << 40 | x << 56 : x);
}
