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
#  define FROM "{" __FILE__ " : " __FUNCTION__ " Ln" __LINE__ "}
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

typedef union					u_mach_header
{
	struct mach_header			mach_hdr32;
	struct mach_header_64		mach_hdr64;
}								t_mach_header;

typedef union					u_segment_command
{
	struct segment_command		seg_cmd32;
	struct segment_command_64	seg_cmd64;
}								t_segment_command;

typedef union					u_section
{
	struct section				sec32;
	struct section_64			sec64;
}								t_section;

typedef union					u_nlist
{
	struct nlist				nlist;
	struct nlist_64				nlist64;
}								t_nlist;

uint32_t						get_sizeofcmds32(t_mach_header *hdr)
{
	return (swap32(hdr->mach_hdr32.sizeofmds));
}
uint32_t						get_sizeofcmds64(t_mach_header *hdr)
{
	return (swap32(hdr->mach_hdr64.sizeofmds));
}

uint32_t						get_ncmds32(t_mach_header *hdr)
{
	return (swap32(hdr->mach_hdr32.ncmds));
}

uint32_t						get_ncmds64(t_mach_header *hdr)
{
	return (swap32(hdr->mach_hdr64.ncmds));
}

uint32_t						get_cmdsize32(t_segment_command *cmd)
{
	return (swap32(cmd->seg_cmd32.cmdsize));
}

uint32_t						get_cmdsize64(t_segment_command *cmd)
{
	return (swap32(cmd->seg_cmd64.cmdsize));
}

uint32_t						get_nsects32(t_segment_command *cmd)
{
	return (swap32(cmd->seg_cmd32.nsects));
}

uint32_t						get_nsects64(t_segment_command *cmd)
{
	return (swap32(cmd->seg_cmd64.nsects));
}

typedef struct					s_funk
{
	size_t						sizeof_mach_header;
	uint32_t					(*get_sizeofcmds)(t_mach_header*);
	uint32_t					(*get_ncmds)(t_mach_header*);
	size_t						sizeof_segment_cmd;
	uint32_t					(*get_cmdsize)(t_segment_command*);
	uint32_t					(*get_nsects)(t_segment_command*);
	size_t						sizeof_section;
	size_t						sizeof_nlist;

}								t_funk;

typedef struct			s_file_info {
	unsigned char const	*ptr;
	size_t				filesize;
	struct				s_bounds {
		size_t			offset;
		size_t			size;
		struct s_bounds	*next;
	}					*boundaries;
}						t_file_info;

typedef bool			(*t_agent)(void);
typedef bool			(*t_section_manager)(size_t);
typedef bool			(*t_lc_manager)(size_t);

bool					g_is_64;

/*
** common.c				=> 4 functions
*/
bool					iterate_load_commands(uint32_t ncmds, uint32_t target, \
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
							char const *from);

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
