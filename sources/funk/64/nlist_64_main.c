/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlist_64_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:18:51 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:19:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_nlist_funk	nlist_funk_64(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist_64), &n_strx_64, &n_type_64, \
		&n_sect_64, &n_desc_64, &n_value_64 });
}
