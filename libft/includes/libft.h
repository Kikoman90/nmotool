/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 13:21:24 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:42:33 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <fcntl.h>

# include <errno.h>
# include <dirent.h>

/*
** ft_toupper.c		=> 1 function
*/
int					ft_toupper(int c);

/*
** ft_strlen.c		=> 1 function
*/
size_t				ft_strlen(char const *str);

/*
** ft_bzero.c		=> 1 function
*/
void				ft_bzero(void *s, size_t n);

/*
** ft_itoa.c		=> 2 functions
*/
char				*ft_itoa(int n);

/*
** ft_strnew.c		=> 1 function
*/
char				*ft_strnew(size_t size);

/*
** ft_strcat.c		=> 1 function
*/
char				*ft_strcat(char *dest, char const *src);

/*
** ft_strcpy.c		=> 2 functions
*/
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t n);

/*
** ft_putchar.c		=> 4 functions
*/
void				ft_putchar(char c);
void				ft_putnchar(char c, size_t n);
void				ft_putchar_fd(short fd, char c);
void				ft_putnchar_fd(short fd, char c, size_t n);

/*
** ft_putstr.c		=> 4 functions
*/
void				ft_putstr(char const *str);
void				ft_putnstr(char const *str, size_t n);
void				ft_putstr_fd(short fd, char const *str);
void				ft_putnstr_fd(short fd, char const *str, size_t n);

/*
** ft_putendl.c		=> 2 functions
*/
void				ft_putendl(char const *str);
void				ft_putendl_fd(short fd, char const *str);

/*
** ft_strjoin.c		=> 4 functions
*/
char				*ft_strjoin_both_free(char *left, char *right);
char				*ft_strjoin_left_free(char *left, char const *right);
char				*ft_strjoin_right_free(char const *left, char *right);
char				*ft_strjoin(char const *left, char const *right);

/*
** ft_strcmp.c		=> 2 functions
*/
int					ft_strcmp(char const *s1, char const *s2);
int					ft_strncmp(char const *s1, char const *s2, size_t n);

#endif
