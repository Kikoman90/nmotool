/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:20:16 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:42:35 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	n_strx(t_nlist const *ptr_nlist)
{
	return (swap32(ptr_nlist->nlist_64.n_un.n_strx));
}

static uint8_t	n_type(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_64.n_type);
}

static uint8_t	n_sect(t_nlist const *ptr_nlist)
{
	return (ptr_nlist->nlist_64.n_sect);
}

static int16_t	n_desc(t_nlist const *ptr_nlist)
{
	return (swap16(ptr_nlist->nlist_64.n_desc));
}

static uint64_t	n_value(t_nlist const *ptr_nlist)
{
	return (swap64(ptr_nlist->nlist_64.n_value));
}

t_nlist_funk	nlist_funk_64(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist_64), &n_strx, &n_type, \
		&n_sect, &n_desc, &n_value });
}
