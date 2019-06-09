/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 15:20:26 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 08:42:33 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "funk.h"

t_header_funk	header64(void)
{
	return ((t_header_funk)\
		{ sizeof(struct mach_header_64), &ncmds64, &sizeofcmds64 });
}

t_segment_funk	segment64(void)
{
	return ((t_segment_funk){ sizeof(struct segment_command_64), \
		&cmdsize64, &nsects64, LC_SEGMENT_64 });
}

t_section_funk	section64(void)
{
	return ((t_section_funk)\
	{ sizeof(struct section_64), &get_sectname64, &get_segname64 });
}

t_nlist_funk	nlist64(void)
{
	return ((t_nlist_funk){ sizeof(struct nlist_64), &n_strx64, &n_type64, \
		&n_sect64, &n_desc64, &n_value64 });
}
