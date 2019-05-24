/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:02:42 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 20:44:21 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

//
# include <stdio.h> // remove me
//

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/arch.h>

# define DEFAULT_TARGET "a.out"

// magic number for archive is "!<arch>\n"
# define AR_MAGIC 0x213C617263683E0A
# define AR_CIGAM 0x0A3E686372613C21

# ifndef NMO_DEBUG
#  define NMO_DEBUG 0
#  define FROM NULL
# elif NMO_DEBUG
#  define FROM "{" __FILE__ " : " __FUNCTION__ " l" __LINE__ "}
# else
#  define FROM NULL
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
	unsigned char const	*ptr;
	struct				s_bounds {
		size_t			offset;
		size_t			size;
		struct s_bounds	*next;
	}					*boundaries;
}						t_file_info;

typedef void			(*t_error_callback)(void);
typedef bool			(*t_agent)(void);
typedef bool			(*t_section_manager)(size_t);
typedef bool			(*t_lc_manager)(size_t);

bool					g_is_64;

/*
** common.c				=> 4 functions
*/
bool					iterate_load_commands(uint32_t target, \
							t_lc_manager funk);
bool					iterate_sections(size_t offset, \
							char const *sectname_target, \
							char const *segname_target, t_section_manager funk);
bool					extract_macho(t_agent agent);

/*
** file.c				=> 3 functions
*/
void					*get_safe(size_t offset, size_t size);
void					pop_bounds(void);
bool					push_bounds(size_t offset, size_t size);
bool					load_file(char const *path);
bool					unload_file(void);

/*
** log.c				=> 1 function
*/
bool					log_error(enum e_error_type type, char const *err, \
							char const *from, t_error_callback callback);

/*
** endian.c				=> 4 functions
*/
void					set_endianness(bool swap_required);
uint16_t				swap16(uint16_t x);
uint32_t				swap32(uint32_t x);
uint64_t				swap64(uint64_t x);

/*
** string.c				=> 5 functions
*/
int						ft_strlen(char const *str);
void					ft_putchar(char c);
void					ft_putchar_fd(short fd, char c);
void					ft_putstr(char const *str);
void					ft_putstr_fd(short fd, char const *str);

#endif
