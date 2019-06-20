/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:28:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/20 20:43:23 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNK_H
# define FUNK_H

# include <ar.h>
# include <mach-o/fat.h>
# include <mach-o/arch.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include "endianness.h"

typedef union					u_mach_header
{
	struct mach_header			header_32;
	struct mach_header_64		header_64;
}								t_mach_header;

typedef struct					s_header_funk
{
	size_t						size_of;
	uint32_t					(*ncmds)(t_mach_header const *);
	uint32_t					(*sizeofcmds)(t_mach_header const *);
}								t_header_funk;

/*
** funk/32/header_32.c			=> 3 functions
*/
t_header_funk					header_funk_32(void);

/*
** funk/64/header_64.c			=> 3 functions
*/
t_header_funk					header_funk_64(void);

typedef union					u_fat_arch
{
	struct fat_arch				fat_arch_32;
	struct fat_arch_64			fat_arch_64;
}								t_fat_arch;

typedef struct					s_fat_arch_funk
{
	size_t						size_of;
	uint64_t					(*offset)(t_fat_arch const *);
	uint64_t					(*size)(t_fat_arch const *);
	cpu_type_t					(*cputype)(t_fat_arch const *);
	cpu_subtype_t				(*cpusubtype)(t_fat_arch const *);
}								t_fat_arch_funk;

/*
** funk/32/fat_arch_32.c		=> 5 functions
*/
t_fat_arch_funk					fat_arch_funk_32(void);

/*
** funk/64/fat_arch_64.c		=> 5 functions
*/
t_fat_arch_funk					fat_arch_funk_64(void);

typedef union					u_segment_command
{
	struct segment_command		segment_32;
	struct segment_command_64	segment_64;
}								t_segment_command;

typedef struct					s_segment_funk
{
	size_t						size_of;
	uint32_t					(*cmdsize)(t_segment_command const *);
	uint32_t					(*nsects)(t_segment_command const *);
	uint32_t					type_of;
}								t_segment_funk;

/*
** funk/32/segment_32.c			=> 3 functions
*/
t_segment_funk					segment_funk_32(void);

/*
** funk/64/segment_64.c			=> 3 functions
*/
t_segment_funk					segment_funk_64(void);

typedef union					u_section
{
	struct section				section_32;
	struct section_64			section_64;
}								t_section;

typedef struct					s_section_funk
{
	size_t						size_of;
	char						*(*get_sectname)(t_section const *, char[16]);
	char						*(*get_segname)(t_section const *, char[16]);
	uint64_t					(*addr)(t_section const *);
	uint64_t					(*size)(t_section const *);
	uint32_t					(*offset)(t_section const *);
}								t_section_funk;

/*
** funk/32/section_32.c			=> 6 functions
*/
t_section_funk					section_funk_32(void);

/*
** funk/64/section_64.c			=> 6 functions
*/
t_section_funk					section_funk_64(void);

typedef union					u_nlist
{
	struct nlist				nlist_32;
	struct nlist_64				nlist_64;
}								t_nlist;

typedef struct					s_nlist_funk
{
	size_t						size_of;
	uint32_t					(*n_strx)(t_nlist const *);
	uint8_t						(*n_type)(t_nlist const *);
	uint8_t						(*n_sect)(t_nlist const *);
	int16_t						(*n_desc)(t_nlist const *);
	uint64_t					(*n_value)(t_nlist const *);
}								t_nlist_funk;

/*
** funk/32/nlist_32.c			=> 6 functions
*/
t_nlist_funk					nlist_funk_32(void);

/*
** funk/64/nlist_64.c			=> 6 functions
*/
t_nlist_funk					nlist_funk_64(void);

typedef struct					s_funk
{
	uint32_t					print_padding;
	t_header_funk				(*header)(void);
	t_segment_funk				(*segment)(void);
	t_section_funk				(*section)(void);
	t_nlist_funk				(*nlist)(void);
}								t_funk;

/*
** funk/funk.c					=> 1 function
*/
t_funk							set_funk(bool is_64);

#endif
