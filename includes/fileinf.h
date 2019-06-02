// 42 header //

#ifndef FILEINF_H
# define FILEINF_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include "logger.h"

// # define BBOX_OVERLAP 0

// struct anonyme: norme ?
typedef struct			s_file_info {
	unsigned char		*ptr;
	struct				s_bbox
	{
		size_t			offset;
		size_t			size;
		struct s_bbox	*next;
	};					*bbounds[3];
}						t_file_info;

typedef enum			s_boxgrade
{
	FILE = 0,
	MACHO = 1,
	TOP = 2
}						t_boxgrade;

# define GGRADE(grade)	(grade == FILE || grade == MACHO || grade == TOP) ? \
							1 : 0;

# define FILE_BOUNDS	file_info.bbounds[FILE]
# define MACHO_BOUNDS	file_info.bbounds[MACHO]
# define TOP_BOUNDS		file_info.bbounds[TOP]

/*
** file_inf.c			=> 5 functions
*/
void					*get_safe(size_t offset, size_t size, t_boxgrade grade);
void					pop_bounds(t_boxgrade grade);
bool					push_bounds(size_t offset, size_t size, \
							t_boxgrade grade);
bool					load_file(char const *path);
bool					unload_file(void);

#endif