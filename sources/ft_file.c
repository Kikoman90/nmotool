/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:26:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/03/11 17:03:23 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void	*ft_file_map(char const *path, size_t *data_size)
{
	int			fd;
	void		*data;
	struct stat	file_stat;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_log_error_null(ERR_FILE, strerror(errno), __func__));
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd);
		return (ft_log_error_null(ERR_FILE, strerror(errno), __func__));
	}
	*data_size = (size_t)file_stat.st_size;
	if ((data = mmap(NULL, *data_size, PROT_READ, MAP_PRIVATE, fd, 0)) \
		== MAP_FAILED)
	{
		close(fd);
		return (ft_log_error_null(ERR_MMAP, strerror(errno), __func__));
	}
	close(fd);
	return (data);
}

void	ft_file_unmap(void *data, size_t fsize, char *fpath)
{
	if (fpath)
	{
		free(fpath);
		fpath = NULL;
	}
	if (data)
	{
		if (munmap(data, fsize) == -1)
			ft_log_error(ERR_MUNMAP, strerror(errno), __func__);	
		data = NULL;
	}
}
