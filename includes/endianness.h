/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:55:43 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/11 19:55:30 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDIANNESS_H
# define ENDIANNESS_H

# include "../libft/includes/libft.h"

/*
** endianness.c	=> 5 functions
*/
void			set_endianness(bool swap_required);
int32_t			signed_swap32(int32_t x);
uint16_t		swap16(uint16_t x);
uint32_t		swap32(uint32_t x);
uint64_t		swap64(uint64_t x);

#endif
