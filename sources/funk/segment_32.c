/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:10 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 13:21:18 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static uint32_t	cmdsize(t_segment_command const *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd_32.cmdsize));
}

static uint32_t	nsects(t_segment_command const *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd_32.nsects));
}

t_segment_funk	segment_funk_32(void)
{
	return ((t_segment_funk)\
		{ sizeof(struct segment_command), &cmdsize, &nsects, LC_SEGMENT });
}
