/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_funk2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:18:15 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 12:19:29 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

char		*get_sectname64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec64.sectname, 16));
}

char		*get_segname64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec64.segname, 16));
}

uint64_t	addr64(t_section const *ptr_section)
{
	return (swap64(ptr_section->sec64.addr));
}

uint64_t	size64(t_section const *ptr_section)
{
	return (swap64(ptr_section->sec64.size));
}

uint32_t	offset64(t_section const *ptr_section)
{
	return (swap32(ptr_section->sec64.offset));
}
