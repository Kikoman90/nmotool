/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 13:16:32 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 13:30:27 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	cmdsize(t_segment_command const *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd_64.cmdsize));
}

static uint32_t	nsects(t_segment_command const *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd_64.nsects));
}

t_segment_funk	segment_funk_64(void)
{
	return ((t_segment_funk){ sizeof(struct segment_command_64), &cmdsize, \
		&nsects, LC_SEGMENT_64 });
}
