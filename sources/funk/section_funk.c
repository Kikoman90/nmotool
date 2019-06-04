/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_funk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 18:28:00 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

char	*get_sectname32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec32.sectname, 16));
}

char	*get_sectname64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec64.sectname, 16));
}

char	*get_segname32(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec32.segname, 16));
}

char	*get_segname64(t_section const *ptr_section, char copy[16])
{
	return (ft_strncpy(copy, ptr_section->sec64.segname, 16));
}
