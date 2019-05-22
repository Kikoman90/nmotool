/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:26:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/22 16:15:59 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

static t_file_info file_info = { NULL, 0, 0 };

void	*get_safe(size_t offset, size_t size)
{
	return ((void *) \
		((size_t)(file_info.ptr + file_info.start_offset + offset) * \
		(file_info.start_offset + offset + size <= file_info.filesize)));
}

bool	load_file(char const *path)
{
	int			fd;
	struct stat	file_stat;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_log_error(ERR_FILE, strerror(errno), __func__));
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd);
		return (ft_log_error(ERR_FILE, strerror(errno), __func__));
	}
	if (file_stat.st_size <= 0)
	{
		close(fd);
		return (ft_log_error(ERR_FILE, "invalid size", __func__));
	}
	file_info.filesize = (size_t)file_stat.st_size;
	if ((file_info.ptr = mmap(NULL, file_info.filesize, PROT_READ, MAP_PRIVATE,
		fd, 0)) == MAP_FAILED)
	{
		close(fd);
		return (ft_log_error(ERR_MMAP, strerror(errno), __func__));
	}
	close(fd);
	return (true);
}

bool	unload_file(void)
{
	if (file_info.ptr)
	{
		if (munmap(file_info.ptr, file_info.filesize) == -1)
			return (ft_log_error(ERR_MUNMAP, strerror(errno), __func__));
		file_info.ptr = NULL;
	}
	return (true);
}
