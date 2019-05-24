/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/05/24 20:41:52 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

// show usage in case of invalid flag or input

/*
bool	nm_set_flag(char const *flag)
{
	if (ft_strlen(flag) >= 2)
		; //return (ft_log_error(ERR_FILE, "missing magic number", __func__)); ERR_FLAG "invalid or unknown flag"
	return (false);
}
*/

bool	manage_segment()//idk
{
	return (true);
}

bool	manage_symtab()//idk
{
	return (true);
}

bool	nm_agent(void)
{
	static uint32_t	segment[] = { LC_SEGMENT, LC_SEGMENT_64 };

	if (!iterate_load_commands(segment[g_is_64], &manage_segment))
		return (log_error(ERR_THROW, "failed to iterate over segment commands",\
			FROM, NULL));
	if (!iterate_load_commands(LC_SYMTAB, &manage_symtab))
		return (log_error(ERR_THROW, "failed to iterate over symtab commands", \
			FROM, NULL));
	return (true);
}

// ce main est immonde
int		main(int argc, char **argv)
{
	if (argc < 2)
	{
		if (!load_file(DEFAULT_TARGET))
			return (EXIT_FAILURE);
		extract_macho(&nm_agent);
		if (!unload_file())
			return (EXIT_FAILURE);
	}
	while (*++argv)
	{
		if (**argv == '-')
		{
			if (!nm_set_flag(*argv))
				return (-1);
		}
		else
		{
			ft_putchar('\n');
			ft_putstr(*argv);
			ft_putstr(":\n");
			if (!load_file(*argv)) {
				extract_macho(*argv, &nm_agent);
				unload_file();
			}
		}
	}
	return (0);
}
