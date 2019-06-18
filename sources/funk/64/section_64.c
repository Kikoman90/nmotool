/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:18:15 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/18 15:19:56 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

char		*get_sectname_64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_64.sectname, 16));
}

char		*get_segname_64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_64.segname, 16));
}

uint64_t	addr_64(t_section const *ptr_section)
{
	return (swap64(ptr_section->section_64.addr));
}

uint64_t	size_64(t_section const *ptr_section)
{
	return (swap64(ptr_section->section_64.size));
}

uint32_t	offset_64(t_section const *ptr_section)
{
	return (swap32(ptr_section->section_64.offset));
}
