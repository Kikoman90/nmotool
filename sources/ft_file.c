/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 14:26:55 by fsidler           #+#    #+#             */
/*   Updated: 2019/02/19 19:31:13 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

void	*ft_file_map(char const *path, size_t *data_size)
{
	int			fd;
	void		*data;
	struct stat	file_stat;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ft_log_error_null("error (open):", strerror(errno))); //ERR_OPEN, strerror(errno), __func__
	if (fstat(fd, &file_stat) == -1)
	{
		close(fd);
		return (ft_log_error_null("error (fstat): ", strerror(errno))); // HERE
	}
	*data_size = (size_t)file_stat.st_size;
	if ((data = mmap(NULL, *data_size, PROT_READ, MAP_PRIVATE, fd, 0)) \
		== MAP_FAILED)
	{
		close(fd);
		return (ft_log_error_null("error (mmap): ", strerror(errno))); // HERE
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
			ft_log_error("error (munmap): ", strerror(errno)); // HERE
		data = NULL;
	}
}
