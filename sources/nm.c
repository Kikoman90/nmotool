/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/02/19 19:34:55 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

bool	nm_set_flag(char const *flag)
{
	(void)flag;
	return (false);
}

void	*extract_macho_header(char const *filename)
{
	size_t	map_size;
	void	*ptr;

	if (!(ptr = ft_file_map(filename, &map_size)))
		return (NULL);
	ft_putstr("MANEME\n");
	return (NULL);
}

int		main(int argc, char **argv)
{
	if (argc < 2)
		extract_macho_header(DEFAULT_TARGET);
	while (*++argv)
	{
		if (**argv == '-' && !nm_set_flag(*argv))
			return (-1);
		if (argc > 2)
		{
			ft_putchar('\n');
			ft_putstr(*argv);
			ft_putstr(":\n");
		}
		extract_macho_header(*argv);
	}
	return (0);
}
