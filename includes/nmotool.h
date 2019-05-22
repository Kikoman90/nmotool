/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfortin <jfortin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:51:23 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/22 17:00:01 by jfortin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NMOTOOL_H
# define NMOTOOL_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>

# include <stdbool.h> // idk about that
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

# define ERR_FILE 0
# define ERR_MMAP 1
# define ERR_MUNMAP 2
# define ERR_THROW 3
# define ERR_N 4

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

bool			g_is_64;

// t_format        

typedef bool    (*t_inspector)(bool);

/*
** ft_file.c	=> 2 functions
*/
void			*get_safe(size_t offset, size_t size);
bool			load_file(char const *path);
bool			unload_file(void);

/*
** ft_string.c	=> 5 functions
*/
int				ft_strlen(char const *str);
void			ft_putchar(char c);
void			ft_putchar_fd(short fd, char c);
void			ft_putstr(char const *str);
void			ft_putstr_fd(short fd, char const *str);

/*
** ft_log.c		=> 2 functions
*/
bool			ft_log_error(unsigned int type, char const *err, \
					char const *from);
// int             ft_logF_error(unsigned int type, char *err, char const *from);
void			*ft_log_error_null(unsigned int type, char const *err, \
					char const *from);
// void            *ft_logF_error_null(unsigned int type, char *err, \
					char const *from);

/*
** ft_endian.c  => 3 functions
*/
void            set_endianness(bool is_little_endian);
uint16_t        ft_swap16(uint16_t x);
uint32_t        ft_swap32(uint32_t x);
uint64_t        ft_swap64(uint64_t x);

#endif
