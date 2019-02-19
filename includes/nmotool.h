/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmotool.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:51:23 by fsidler           #+#    #+#             */
/*   Updated: 2019/02/19 19:34:15 by fsidler          ###   ########.fr       */
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
# include <mach-o/nlist.h>

# define DEFAULT_TARGET "a.out"

/*
** ft_file.c	=> 2 functions
*/
void			*ft_file_map(char const *path, size_t *data_size);
void			ft_file_unmap(void *data, size_t fsize, char *fpath);

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
int				ft_log_error(char const *str1, char const *str2);
void			*ft_log_error_null(char const *str1, char const *str2);

#endif
