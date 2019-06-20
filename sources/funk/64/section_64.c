/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 12:18:15 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:42:34 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

static char		*get_sectname(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_64.sectname, 16));
}

static char		*get_segname(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->section_64.segname, 16));
}

static uint64_t	addr(t_section const *ptr_section)
{
	return (swap64(ptr_section->section_64.addr));
}

static uint64_t	size(t_section const *ptr_section)
{
	return (swap64(ptr_section->section_64.size));
}

static uint32_t	offset(t_section const *ptr_section)
{
	return (swap32(ptr_section->section_64.offset));
}

t_section_funk	section_funk_64(void)
{
	return ((t_section_funk){ sizeof(struct section_64), &get_sectname, \
		&get_segname, &addr, &size, &offset });
}
