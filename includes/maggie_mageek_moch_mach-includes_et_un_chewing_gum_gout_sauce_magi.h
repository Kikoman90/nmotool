/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maggie_mageek_moch_mach-includes_et_un_chew        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:56:07 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/04 16:56:08 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAGGIE_MAGEEK_MOCH_MACH_INCLUDES_ET_UN_CHEWING_GUM_GOUT_SAUCE_MAGI_H
# define MAGGIE_MAGEEK_MOCH_MACH_INCLUDES_ET_UN_CHEWING_GUM_GOUT_SAUCE_MAGI_H

// # include <mach-o/arch.h>
# include <ar.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>

# define B_IG_MACH_O_ZONIONS	1
# define B_IG_MAZO_CHISTE		1

# define IS_MH_CIGAM(magic)		(magic == MH_CIGAM || magic == MH_CIGAM_64)
# define IS_FAT_CIGAM(magic)	(magic == FAT_CIGAM || magic == FAT_CIGAM_64)
# define MAGIC_IS_CIGAM(magic)	(IS_MH_CIGAM(magic) || IS_FAT_CIGAM(magic))

# define IS_MH_64(magic)		(magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
# define IS_FAT_64(magic)		(magic == FAT_MAGIC_64 || magic == FAT_CIGAM_64)
# define MAGIC_IS_64(magic)		(IS_MH_64(magic) || IS_FAT_64(magic))

# define MH_CIGAM_(_64)			_64 ? MH_CIGAM_64 : MH_CIGAM
# define MH_MAGIC_(_64)			_64 ? MH_MAGIC_64 : MH_MAGIC
# define FAT_CIGAM_(_64)		_64 ? FAT_CIGAM_64 : FAT_CIGAM
# define FAT_MAGIC_(_64)		_64 ? FAT_MAGIC_64 : FAT_MAGIC

#endif
