/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:51:23 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/22 20:09:57 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NMOTOOL_H
# define NMOTOOL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>

# ifndef NMOTOOL_DEBUG
#  define NMOTOOL_DEBUG 0
# endif

# include <stdio.h> // remove me

# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/arch.h>
# include <mach-o/nlist.h>

# define DEFAULT_TARGET "a.out"

# define NMO_ERR_OUT "\033[4;31m"
# define NMO_CLR_OUT "\033[0m\n"

// bitwise operators :
// ~A : bitwise NOT (one's complement) (unary)
// A & B : bitwise AND
// A | B : bitwise OR
// A ^ B : bitwise XOR
// <<, >> : left and right shift
// bitwise assignment operators : &=, |=, ^=, <<=, >>=
// logical operators : &&, ||, !, !=

typedef unsigned char   t_uchar;

typedef struct          s_nm_stack {
	void                *data;
	struct s_sizestack  *next;
}                       t_nm_stack;

typedef struct			s_file_info {
	t_uchar const *		ptr;
	size_t				filesize;
	size_t				start_offset;
}						t_file_info;

enum e_error_type {
	ERR_FILE = 0,
	ERR_MMAP,
	ERR_MUNMAP,
	ERR_THROW,
	ERR_N
};

bool				g_is_64;   

typedef bool		(*t_inspector)(bool);

/*
** file.c		=> 3 functions
*/
void			*get_safe(size_t offset, size_t size);
bool			load_file(char const *path);
bool			unload_file(void);

/*
** string.c		=> 5 functions
*/
int				ft_strlen(char const *str);
void			ft_putchar(char c);
void			ft_putchar_fd(short fd, char c);
void			ft_putstr(char const *str);
void			ft_putstr_fd(short fd, char const *str);

/*
** log.c		=> 2 functions
*/
bool			log_error(unsigned int type, char const *err, char const *from);
void			*log_error_null(unsigned int type, char const *err, \
					char const *from);

/*
** endian.c		=> 4 functions
*/
void            set_endianness(bool swap_required);
uint16_t        swap16(uint16_t x);
uint32_t        swap32(uint32_t x);
uint64_t        swap64(uint64_t x);

#endif
