/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:21:07 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

char		*get_sectname_32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_32.sectname, 16));
}

char		*get_segname_32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_32.segname, 16));
}

uint64_t	addr_32(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->section_32.addr));
}

uint64_t	size_32(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->section_32.size));
}

uint32_t	offset_32(t_section const *ptr_section)
{
	return (swap32(ptr_section->section_32.offset));
}
