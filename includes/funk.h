/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funk.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:28:19 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/29 15:09:33 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNK_H
# define FUNK_H

# include "maggie_mageek_moch_mach-includes_et_un_chewing_gum_gout_sauce_magi.h"
# include "endianness.h"

typedef union					u_mach_header
{
	struct mach_header			mach_hdr32;
	struct mach_header_64		mach_hdr64;
}								t_mach_header;

typedef struct					s_header_funk
{
	size_t						size_of; // size of mach-o header
	uint32_t					(*ncmds)(t_mach_header*);
	uint32_t					(*sizeofcmds)(t_mach_header*);
}								t_header_funk;

/*
** funk/header_funk.c			=> 4 functions 
*/
uint32_t						ncmds32(t_mach_header *ptr_hdr);
uint32_t						ncmds64(t_mach_header *ptr_hdr);
uint32_t						sizeofcmds32(t_mach_header *ptr_hdr);
uint32_t						sizeofcmds64(t_mach_header *ptr_hdr);

typedef union					u_segment_command
{
	struct segment_command		seg_cmd32;
	struct segment_command_64	seg_cmd64;
}								t_segment_command;

typedef struct					s_segment_funk
{
	size_t						size_of; // size of segment command
	uint32_t					(*cmdsize)(t_segment_command*);
	uint32_t					(*nsects)(t_segment_command*);
	uint32_t					type_of; // type of segment command
}								t_segment_funk;

/*
** funk/segment_funk.c			=> 4 functions
*/
uint32_t						cmdsize32(t_segment_command *ptr_cmd);
uint32_t						cmdsize64(t_segment_command *ptr_cmd);
uint32_t						nsects32(t_segment_command *ptr_cmd);
uint32_t						nsects64(t_segment_command *ptr_cmd);

typedef union					u_section
{
	struct section				sec32;
	struct section_64			sec64;
}								t_section;


typedef struct					s_section_funk
{
	size_t						size_of;
	char *						(*sectname)(t_section*);
	char *						(*segname)(t_section*);
}								t_section_funk;

/*
** funk/section_funk.c			=> 4 functions
*/
char							*sectname32(t_section *ptr_section);
char							*sectname64(t_section *ptr_section);
char							*segname32(t_section *ptr_section);
char							*segname64(t_section *ptr_section);

typedef union					u_nlist
{
	struct nlist				nlist32;
	struct nlist_64				nlist64;
}								t_nlist;

typedef struct					s_nlist_funk
{
	size_t						size_of;
	uint32_t					(*n_strx)(t_nlist *ptr_nlist);
	uint8_t						(*n_type)(t_nlist *ptr_nlist);
	uint8_t						(*n_sect)(t_nlist *ptr_nlist);
	int16_t						(*n_desc)(t_nlist *ptr_nlist);
	uint64_t					(*n_value)(t_nlist *ptr_nlist);
}								t_nlist_funk;

/*
** funk/nlist_funk1.c			=> 5 functions
*/
uint32_t						n_strx32(t_nlist *ptr_nlist);
uint8_t							n_type32(t_nlist *ptr_nlist);
uint8_t							n_sect32(t_nlist *ptr_nlist);
int16_t							n_desc32(t_nlist *ptr_nlist);
uint64_t						n_value32(t_nlist *ptr_nlist);

/*
** funk/nlist_funk2.c			=> 5 functions
*/
uint32_t						n_strx64(t_nlist *ptr_nlist);
uint8_t							n_type64(t_nlist *ptr_nlist);
uint8_t							n_sect64(t_nlist *ptr_nlist);
int16_t							n_desc64(t_nlist *ptr_nlist);
uint64_t						n_value64(t_nlist *ptr_nlist);

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
