/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:42 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 21:01:28 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

//
# include <stdio.h>
//

# include <ar.h>

# include "../libft/includes/libft.h"

# include "funk.h"

# define DEFAULT_TARGET "a.out"

# ifndef NMO_DEBUG
#  define NMO_DEBUG 0
#  define FROM NULL
# elif NMO_DEBUG
#  define FROM log_from(__FILE__, __FUNCTION__, __LINE__)
# else
#  define FROM
# endif

# define ERROR_CLR "\033[4;31m"
# define CLEAR_CLR "\033[0m\n"

enum					e_error_type {
	ERR_FILE = 0,
	ERR_MMAP,
	ERR_MUNMAP,
	ERR_MALLOC,
	ERR_THROW,
	ERR_N
};

typedef struct			s_file_info {
	unsigned char		*ptr;
	size_t				filesize;
	struct				s_bounds {
		size_t			offset;
		size_t			size;
		struct s_bounds	*next;
	}					*boundaries;
}						t_file_info;

typedef bool			(*t_agent)(void);
typedef void			(*t_funk)(bool);
typedef void			(*t_section_manager)(size_t);
typedef bool			(*t_lc_manager)(size_t);

/*
** macho.c				=> 5 functions
*/
void					set_section_funk(bool is_64);
bool					iterate_load_commands(uint32_t ncmds, uint32_t target, \
							t_lc_manager funk);
bool					iterate_sections(uint32_t nsects, \
							char const *sectname_target, \
							char const *segname_target, t_section_manager funk);
bool					extract_macho(char const *filepath, t_agent agent, \
							t_funk funk);

/*
** file.c				=> 6 functions
*/
void					*get_safe(size_t offset, size_t size);
size_t					get_current_offset(void);
void					pop_bounds(void);
bool					push_bounds(size_t offset, size_t size);
bool					load_file(char const *path);
bool					unload_file(void);

/*
** log.c				=> 2 function
*/
char					*log_from(char const *file, char const *func, \
							uint32_t line);
bool					log_error(enum e_error_type type, char const *err, \
							char *from);

/*
** endian.c				=> 4 functions
*/
void					set_endianness(bool swap_required);
uint16_t				swap16(uint16_t x);
uint32_t				swap32(uint32_t x);
uint64_t				swap64(uint64_t x);

#endif
