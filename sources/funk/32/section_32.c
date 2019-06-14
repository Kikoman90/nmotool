/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 14:55:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static char		*get_sectname(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_32.sectname, 16));
}

static char		*get_segname(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_32.segname, 16));
}

static uint64_t	addr(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->section_32.addr));
}

static uint64_t	size(t_section const *ptr_section)
{
	return ((uint64_t)swap32(ptr_section->section_32.size));
}

static uint32_t	offset(t_section const *ptr_section)
{
	return (swap32(ptr_section->section_32.offset));
}

t_section_funk	section_funk_32(void)
{
	return ((t_section_funk){ sizeof(struct section), &get_sectname, \
		&get_segname, &addr, &size, &offset });
}
