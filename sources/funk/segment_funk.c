/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_funk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:10 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/28 16:24:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

uint32_t	cmdsize32(t_segment_command *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd32.cmdsize));
}

uint32_t	cmdsize64(t_segment_command *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd64.cmdsize));
}

uint32_t	nsects32(t_segment_command *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd32.nsects));
}

uint32_t	nsects64(t_segment_command *ptr_cmd)
{
	return (swap32(ptr_cmd->seg_cmd64.nsects));
}