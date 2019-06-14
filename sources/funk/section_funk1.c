/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_funk1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 12:23:21 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

char		*get_sectname32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec32.sectname, 16));
}

char		*get_segname32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec32.segname, 16));
}

uint64_t	addr32(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->sec32.addr));
}

uint64_t	size32(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->sec32.size));
}

uint32_t	offset32(t_section const *ptr_section)
{
	return (swap32(ptr_section->sec32.offset));
}
