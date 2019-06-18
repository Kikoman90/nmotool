/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_64_main.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:20:05 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:20:22 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_section_funk	section_funk_64(void)
{
	return ((t_section_funk){ sizeof(struct section_64), &get_sectname_64, \
		&get_segname_64, &addr_64, &size_64, &offset_64 });
}
