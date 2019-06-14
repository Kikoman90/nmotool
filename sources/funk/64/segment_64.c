/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:16:32 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 14:53:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	cmdsize(t_segment_command const *ptr_segment)
{
	return (swap32(ptr_segment->segment_64.cmdsize));
}

static uint32_t	nsects(t_segment_command const *ptr_segment)
{
	return (swap32(ptr_segment->segment_64.nsects));
}

t_segment_funk	segment_funk_64(void)
{
	return ((t_segment_funk){ sizeof(struct segment_command_64), &cmdsize, \
		&nsects, LC_SEGMENT_64 });
}
