/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_lf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 12:15:37 by fsidler           #+#    #+#             */
/*   Updated: 2018/09/18 12:15:40 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_lf(char *s1, char const *s2)
{
	char	*n;
	int		i[2];

	i[0] = 0;
	while (s1[i[0]])
		i[0]++;
	i[1] = 0;
	while (s2[i[1]])
		i[1]++;
	n = (char *)malloc(sizeof(char) * (i[0] + i[1] + 1));
	i[0] = 0;
	while (s1[i[0]])
	{
		n[i[0]] = s1[i[0]];
		i[0]++;
	}
	i[1] = 0;
	while (s2[i[1]])
	{
		n[i[0] + i[1]] = s2[i[1]];
		i[1]++;
	}
	n[i[0] + i[1]] = '\0';
	free(s1);
	return (n);
}