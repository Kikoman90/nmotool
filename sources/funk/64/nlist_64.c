/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:20:16 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:18:41 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

uint32_t	n_strx_64(t_nlist const *ptr_nlist)
{
	return (swap32(ptr_nlist->nlist_64.n_un.n_strx));
}

uint8_t		n_type_64(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_64.n_type);
}

uint8_t		n_sect_64(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_64.n_sect);
}

int16_t		n_desc_64(t_nlist const *ptr_nlist)
{
	return (swap16(ptr_nlist->nlist_64.n_desc));
}

uint64_t	n_value_64(t_nlist const *ptr_nlist)
{
	return (swap64(ptr_nlist->nlist_64.n_value));
}
