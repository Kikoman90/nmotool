/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:26:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 21:01:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static t_file_info file_info = { NULL, 0, NULL };

void	*get_safe(size_t offset, size_t size)
{
	struct s_bounds	*top;

	if (offset + size < offset)
		return (NULL);
	if ((top = file_info.boundaries))
		return ((offset + size <= top->size) ? \
			(void*)((size_t)file_info.ptr + top->offset + offset) : NULL);
	else if (offset + size <= file_info.filesize)
		return ((void*)((size_t)file_info.ptr + offset));
	return (NULL);
}

size_t	get_current_offset(void)
{
	if (file_info.boundaries)
		return (file_info.boundaries->offset);
	return (0);
}

void	pop_bounds(void)
{
	struct s_bounds	*top;

	if ((top = file_info.boundaries)) {
		file_info.boundaries = file_info.boundaries->next;
		free(top);
	}
}

bool	push_bounds(size_t offset, size_t size)
{
	struct s_bounds	*top;
	struct s_bounds	*new;

	top = file_info.boundaries;
	if (offset + size > file_info.filesize || offset + size < offset)
		return (log_error(ERR_FILE, "invalid bounds", FROM));
	if (!(new = (struct s_bounds*)malloc(sizeof(*new))))
		return (log_error(ERR_MALLOC, strerror(errno), FROM));
	new->offset = offset;
	new->size = size;
	new->next = top;
	file_info.boundaries = new;
	return (true);
}

// cleanup required
bool	load_file(char const *path)
{
	int			fd;
	struct stat	file_stat;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (log_error(ERR_FILE, strerror(errno), FROM));
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd); // close can fail
		return (log_error(ERR_FILE, strerror(errno), FROM));
	}
	// check (file_stat.st_mode & S_IFDIR) -> is directory !
	if (file_stat.st_size <= 0)
	{
		close(fd); // close can fail
		return (log_error(ERR_FILE, "invalid size", FROM));
	}
	file_info.filesize = (size_t)file_stat.st_size;
	if ((file_info.ptr = mmap(NULL, file_info.filesize, \
		PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
	{
		close(fd); // close can fail
		return (log_error(ERR_MMAP, strerror(errno), FROM));
	}
	close(fd); // close can fail
	return (true);
}

// cleanup required
bool	unload_file(void)
{
	while (file_info.boundaries)
		pop_bounds();
	if (file_info.ptr && file_info.ptr != MAP_FAILED && file_info.boundaries)
	{
		if (munmap(file_info.ptr, file_info.filesize) == -1)
			return (log_error(ERR_MUNMAP, strerror(errno), FROM));
		file_info.ptr = NULL;
	}
	return (true);
}
