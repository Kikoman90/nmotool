// 42 header //

#include "endianness.h"

static bool endian_swap = false;

void		set_endianness(bool swap_required)
{
	endian_swap = swap_required;
}

uint16_t	swap16(uint16_t x)
{
	return (endian_swap ? x >> 8 | x << 8 : x);
}

uint32_t	swap32(uint32_t x)
{
	return (endian_swap ? x >> 24 | (x & 0x00ff0000) >> 8 \
		| (x & 0x0000ff00) << 8 | x << 24 : x);
}

uint64_t	swap64(uint64_t x)
{
	return (endian_swap ? x >> 56 | (x & 0x00ff000000000000ULL) >> 40 \
		| (x & 0x0000ff0000000000ULL) >> 24 | (x & 0x000000ff00000000ULL) >>  8 \
		| (x & 0x00000000ff000000ULL) <<  8 | (x & 0x0000000000ff0000ULL) << 24 \
		| (x & 0x000000000000ff00ULL) << 40 | x << 56 : x);
}
