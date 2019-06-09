/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:22:32 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 08:42:37 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_header_funk	header32(void)
{
	return ((t_header_funk)\
		{ sizeof(struct mach_header), &ncmds32, &sizeofcmds32 });
}

t_segment_funk	segment32(void)
{
	return ((t_segment_funk)\
		{ sizeof(struct segment_command), &cmdsize32, &nsects32, LC_SEGMENT });
}

t_section_funk	section32(void)
{
	return ((t_section_funk)\
		{ sizeof(struct section), &get_sectname32, &get_segname32 });
}

t_nlist_funk	nlist32(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist), &n_strx32, &n_type32, \
		&n_sect32, &n_desc32, &n_value32 });
}
