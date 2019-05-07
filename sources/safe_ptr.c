/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:23:08 by fsidler           #+#    #+#             */
/*   Updated: 2019/03/11 15:55:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static t_safe_pointer	safe_pointer = { NULL, 0, 0 };

void	init_safe_pointer(void *ptr, size_t size) {
	safe_pointer.ptr = ptr;
	safe_pointer.filesize = size;
}

void	*get_safe(size_t offset, size_t size)
{
	return ((void *) \
		((size_t)(safe_pointer.ptr + safe_pointer.start_offset + offset) * \
		(safe_pointer.start_offset + offset + size <= safe_pointer.filesize)));
}
