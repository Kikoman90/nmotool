/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:19:10 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 09:55:23 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_info.h"

static t_file_info g_file_info = { NULL, { NULL, NULL, NULL } };

void	*get_safe(size_t offset, size_t size, t_bounds_target b_target)
{
	struct s_bounds	*bounds;

	if (offset + size < offset)
		return (NULL);
	if (VALID_BT(b_target))
	{
		if (!(bounds = g_file_info.bounds[b_target]))
			return (log_error_null(ERR_THROW, "invalid target bounds", FROM));
		if (offset + size > bounds->size)
			return (log_error_null(ERR_THROW, "pointer out of bounds", FROM));
		while (bounds)
		{
			if (offset + bounds->offset < offset)
				return (NULL);
			offset += bounds->offset;
			bounds = bounds->next;
		}
		return ((void*)(g_file_info.ptr + offset));
	}
	return (log_error_null(ERR_THROW, "invalid bounds target !", FROM));
}

void	pop_bounds(t_bounds_target b_target)
{
	struct s_bounds	*pop;

	pop = NULL;
	if (VALID_BT(b_target) && (pop = g_file_info.bounds[b_target]))
	{
		if (b_target == BT_TOP)
			TOP_BOUNDS = (pop->next != MACHO_BOUNDS) ? pop->next : NULL;
		else if (b_target == BT_MACHO)
		{
			while (TOP_BOUNDS)
				pop_bounds(BT_TOP);
			MACHO_BOUNDS = NULL;
		}
		else if (b_target == BT_FILE)
		{
			pop_bounds(BT_MACHO);
			FILE_BOUNDS = NULL;
		}
		free(pop);
	}
}

bool	push_bounds(size_t offset, size_t size, t_bounds_target b_target)
{
	struct s_bounds	*newt;
	struct s_bounds	*next;

	if (offset + size < offset)
		return (NULL);
	if (!VALID_BT(b_target))
		return (log_error(ERR_THROW, "invalid bounds target !", FROM));
	if (b_target == BT_TOP && !(next = TOP_BOUNDS))
	{
		if (!(next = MACHO_BOUNDS))
			return (log_error(ERR_THROW, "missing macho bounds", FROM));
	}
	else if (b_target == BT_MACHO && !(next = FILE_BOUNDS))
		return (log_error(ERR_THROW, "missing file bounds", FROM));
	if (b_target != BT_FILE && offset + size > next->size)
		return (log_error(ERR_THROW, "invalid bounds", FROM));
	if (!(newt = (struct s_bounds*)malloc(sizeof(*newt))))
		return (log_error(ERR_MALLOC, strerror(errno), FROM));
	newt->offset = offset;
	newt->size = size;
	newt->next = (b_target == BT_FILE) ? NULL : next;
	if (b_target != BT_TOP)
		pop_bounds(b_target);
	g_file_info.bounds[b_target] = newt;
	return (true);
}

bool	unload_file(void)
{
	if (g_file_info.ptr && g_file_info.ptr != MAP_FAILED && FILE_BOUNDS)
	{
		if (munmap(g_file_info.ptr, FILE_BOUNDS->size) == -1)
		{
			pop_bounds(BT_FILE);
			return (log_error(ERR_MUNMAP, strerror(errno), FROM));
		}
		g_file_info.ptr = NULL;
	}
	pop_bounds(BT_FILE);
	return (true);
}

bool	load_file(char const *path, size_t *ptr_filesize)
{
	int			fd;
	bool		ret;
	struct stat	file_stat;

	ret = true;
	if ((fd = open(path, O_RDONLY)) == -1)
		return (log_error(ERR_FILE, strerror(errno), FROM));
	if (fstat(fd, &file_stat) == -1)
		ret = log_error(ERR_FILE, strerror(errno), FROM);
	else if (file_stat.st_mode & S_IFDIR)
		ret = log_error(ERR_FILE, "parameter must not be a directory", FROM);
	else if (file_stat.st_size <= 0)
		ret = log_error(ERR_FILE, "invalid file size", FROM);
	else
	{
		*ptr_filesize = (size_t)file_stat.st_size;
		if (!push_bounds(0, *ptr_filesize, BT_FILE))
			ret = log_error(ERR_THROW, "failed to set file boundaries", FROM);
		else if ((g_file_info.ptr = mmap(NULL, *ptr_filesize, \
			PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			ret = log_error(ERR_MMAP, strerror(errno), FROM);
	}
	return ((close(fd) == -1) ? \
		log_error(ERR_FILE, strerror(errno), FROM) : ret);
}
