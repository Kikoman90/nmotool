/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:28:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 08:52:42 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNK_H
# define FUNK_H

// # include <mach-o/arch.h>
# include <ar.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# include "endianness.h"

typedef union					u_mach_header
{
	struct mach_header			mach_hdr32;
	struct mach_header_64		mach_hdr64;
}								t_mach_header;

typedef struct					s_header_funk
{
	size_t						size_of;
	uint32_t					(*ncmds)(t_mach_header const *);
	uint32_t					(*sizeofcmds)(t_mach_header const *);
}								t_header_funk;

/*
** funk/header_funk.c			=> 4 functions
*/
uint32_t						ncmds32(t_mach_header const *ptr_hdr);
uint32_t						ncmds64(t_mach_header const *ptr_hdr);
uint32_t						sizeofcmds32(t_mach_header const *ptr_hdr);
uint32_t						sizeofcmds64(t_mach_header const *ptr_hdr);

typedef union					u_fat_arch
{
	struct fat_arch				fat_arch32;
	struct fat_arch_64			fat_arch64;
}								t_fat_arch;

typedef struct					s_fat_arch_funk
{
	size_t						size_of;
	uint64_t					(*offset)(t_fat_arch const *);
	uint64_t					(*size)(t_fat_arch const *);
}								t_fat_arch_funk;

/*
** funk/fat_arch_funk.c			=> 4 functions
*/
uint64_t						offset32(t_fat_arch const *fata);
uint64_t						offset64(t_fat_arch const *fata);
uint64_t						size32(t_fat_arch const *fata);
uint64_t						size64(t_fat_arch const *fata);

typedef union					u_segment_command
{
	struct segment_command		seg_cmd32;
	struct segment_command_64	seg_cmd64;
}								t_segment_command;

typedef struct					s_segment_funk
{
	size_t						size_of;
	uint32_t					(*cmdsize)(t_segment_command const *);
	uint32_t					(*nsects)(t_segment_command const *);
	uint32_t					type_of;
}								t_segment_funk;

/*
** funk/segment_funk.c			=> 4 functions
*/
uint32_t						cmdsize32(t_segment_command const *ptr_cmd);
uint32_t						cmdsize64(t_segment_command const *ptr_cmd);
uint32_t						nsects32(t_segment_command const *ptr_cmd);
uint32_t						nsects64(t_segment_command const *ptr_cmd);

typedef union					u_section
{
	struct section				sec32;
	struct section_64			sec64;
}								t_section;

typedef struct					s_section_funk
{
	size_t						size_of;
	char						*(*get_sectname)(t_section const *, char[16]);
	char						*(*get_segname)(t_section const *, char[16]);
}								t_section_funk;

/*
** funk/section_funk.c			=> 4 functions
*/
char							*get_sectname32(t_section const *ptr_section, \
									char copy[16]);
char							*get_sectname64(t_section const *ptr_section, \
									char copy[16]);
char							*get_segname32(t_section const *ptr_section, \
									char copy[16]);
char							*get_segname64(t_section const *ptr_section, \
									char copy[16]);

typedef union					u_nlist
{
	struct nlist				nlist32;
	struct nlist_64				nlist64;
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
** funk/nlist_funk1.c			=> 5 functions
*/
uint32_t						n_strx32(t_nlist const *ptr_nlist);
uint8_t							n_type32(t_nlist const *ptr_nlist);
uint8_t							n_sect32(t_nlist const *ptr_nlist);
int16_t							n_desc32(t_nlist const *ptr_nlist);
uint64_t						n_value32(t_nlist const *ptr_nlist);

/*
** funk/nlist_funk2.c			=> 5 functions
*/
uint32_t						n_strx64(t_nlist const *ptr_nlist);
uint8_t							n_type64(t_nlist const *ptr_nlist);
uint8_t							n_sect64(t_nlist const *ptr_nlist);
int16_t							n_desc64(t_nlist const *ptr_nlist);
uint64_t						n_value64(t_nlist const *ptr_nlist);

typedef struct					s_funk
{
	t_header_funk				(*header)(void);
	t_segment_funk				(*segment)(void);
	t_section_funk				(*section)(void);
	t_nlist_funk				(*nlist)(void);
}								t_funk;

/*
** funk/funk1.c					=> 4 functions
*/
t_header_funk					header32(void);
t_segment_funk					segment32(void);
t_section_funk					section32(void);
t_nlist_funk					nlist32(void);

/*
** funk/funk2.c					=> 4 functions
*/
t_header_funk					header64(void);
t_segment_funk					segment64(void);
t_section_funk					section64(void);
t_nlist_funk					nlist64(void);

#endif
