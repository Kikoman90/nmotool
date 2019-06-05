/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/21 18:49:01 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/05 18:17:19 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_both_free(char *left, char *right)
{
	char	*str;

	str = ft_strjoin(left, right);
	free(left);
	free(right);
	return (str);
}

char	*ft_strjoin_left_free(char *left, char const *right)
{
	char	*str;

	str = ft_strjoin(left, right);
	free(left);
	return (str);
}

char	*ft_strjoin_right_free(char const *left, char *right)
{
	char	*str;

	str = ft_strjoin(left, right);
	free(right);
	return (str);
}

char	*ft_strjoin(char const *left, char const *right)
{
	char	*str;

	if (!left || !right \
		|| !(str = ft_strnew(ft_strlen(left) + ft_strlen(right))))
		return (NULL);
	ft_strcpy(str, left);
	ft_strcat(str, right);
	return (str);
}
