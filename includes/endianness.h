// 42 header //

#ifndef ENDIANNESS_H
# define ENDIANNESS_H

# include "../libft/includes/libft.h"

/*
** endianness.c	=> 4 functions
*/
void			set_endianness(bool swap_required);
uint16_t		swap16(uint16_t x);
uint32_t		swap32(uint32_t x);
uint64_t		swap64(uint64_t x);

#endif