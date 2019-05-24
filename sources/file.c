/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:26:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 19:47:39 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static t_file_info file_info = { NULL, NULL };

void	*get_safe(size_t offset, size_t size)
{
	struct s_bounds	*top;

	if (offset + size < offset)
		return (NULL);
	if ((top = file_info.boundaries) && (offset + size <= top->size))
	{
		while (top)
		{
			offset += top->offset;
			top = top->next;	
		}
		return ((void*)((size_t)file_info.ptr + offset));
	}
	return (NULL);
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

	if ((top = file_info.boundaries) && offset + size > top->size)
		return (log_error(ERR_FILE, "invalid bounds", FROM, NULL));
	if (!(new = (struct s_bounds*)malloc(sizeof(*new))))
		return (log_error(ERR_MALLOC, strerror(errno), FROM, NULL));
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
		return (ft_log_error(ERR_FILE, strerror(errno), __func__));
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd); // close can fail
		return (ft_log_error(ERR_FILE, strerror(errno), __func__));
	}
	// check (file_stat.st_mode & S_IFDIR) -> is directory !
	if (file_stat.st_size <= 0)
	{
		close(fd); // close can fail
		return (ft_log_error(ERR_FILE, "invalid size", __func__));
	}
	if ((file_info.ptr = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE,
		fd, 0)) == MAP_FAILED)
	{
		close(fd); // close can fail
		return (ft_log_error(ERR_MMAP, strerror(errno), __func__));
	}
	if (!push_bounds(0, (size_t)file_stat.st_size))
	{
		// munmap() !!
		close(fd); // close can fail
		return (log_error(ERR_THROW, "could not set file size", FROM, NULL));
	}
	close(fd); // close can fail
	return (true);
}

// cleanup required
bool	unload_file(void)
{
	if (file_info.ptr && file_info.ptr != MAP_FAILED && file_info.boundaries)
	{
		if (munmap(file_info.ptr, file_info.boundaries->size) == -1)
			return (ft_log_error(ERR_MUNMAP, strerror(errno), __func__));
		file_info.ptr = NULL;
	}
	while (file_info.boundaries)
		pop_bounds();
	return (true);
}
