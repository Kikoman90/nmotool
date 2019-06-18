/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_32_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:14:25 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:17:54 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_nlist_funk	nlist_funk_32(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist), &n_strx_32, &n_type_32, \
		&n_sect_32, &n_desc_32, &n_value_32 });
}
