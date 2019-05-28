/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_funk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:30:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/28 16:26:45 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

char		*sectname32(t_section *ptr_section)
{
	return (ptr_section->sec32.sectname);
}

char		*sectname64(t_section *ptr_section)
{
	return (ptr_section->sec64.sectname);
}

char		*segname32(t_section *ptr_section)
{
	return (ptr_section->sec32.segname);
}

char		*segname64(t_section *ptr_section)
{
	return (ptr_section->sec64.segname);
}
