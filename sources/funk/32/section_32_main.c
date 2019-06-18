/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_32_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:21:14 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:21:18 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_section_funk	section_funk_32(void)
{
	return ((t_section_funk){ sizeof(struct section), &get_sectname_32, \
		&get_segname_32, &addr_32, &size_32, &offset_32 });
}
