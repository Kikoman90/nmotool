/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:20:07 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:15:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

uint32_t	n_strx_32(t_nlist const *ptr_nlist)
{
	return (swap32(ptr_nlist->nlist_32.n_un.n_strx));
}

uint8_t		n_type_32(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_32.n_type);
}

uint8_t		n_sect_32(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_32.n_sect);
}

int16_t		n_desc_32(t_nlist const *ptr_nlist)
{
	return (swap16(ptr_nlist->nlist_32.n_desc));
}

uint64_t	n_value_32(t_nlist const *ptr_nlist)
{
	return ((uint64_t)swap32(ptr_nlist->nlist_32.n_value));
}
