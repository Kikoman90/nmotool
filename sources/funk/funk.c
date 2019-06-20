/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 15:07:06 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:53:19 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_funk	set_funk(bool is_64)
{
	return ((is_64) ? \
		(t_funk){ 16, &header_funk_64, &segment_funk_64, &section_funk_64, \
		&nlist_funk_64 } : (t_funk){ 8, &header_funk_32, &segment_funk_32, \
		&section_funk_32, &nlist_funk_32 });
}
