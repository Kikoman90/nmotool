/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 14:28:36 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:44:32 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_INFO_H
# define FILE_INFO_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include "logger.h"

typedef struct			s_file_info {
	unsigned char		*ptr;
	struct				s_bounds {
		size_t			offset;
		size_t			size;
		struct s_bounds	*next;
	}					*bounds[3];
}						t_file_info;

typedef enum			e_bounds_target {
	BT_FILE = 0,
	BT_MACHO = 1,
	BT_TOP = 2
}						t_bounds_target;

# define VALID_BT(t)	(t == BT_FILE || t == BT_MACHO || t == BT_TOP)

# define FILE_BOUNDS	g_file_info.bounds[BT_FILE]
# define MACHO_BOUNDS	g_file_info.bounds[BT_MACHO]
# define TOP_BOUNDS		g_file_info.bounds[BT_TOP]

/*
** file_info.c			=> 5 functions
*/
void					*get_safe(size_t offset, size_t size, \
							t_bounds_target b_target);
void					pop_bounds(t_bounds_target b_target);
bool					push_bounds(size_t offset, size_t size, \
							t_bounds_target b_target);
bool					unload_file(void);
bool					load_file(char const *path, size_t *ptr_filesize);

#endif
