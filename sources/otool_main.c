/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:22:00 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/14 11:19:24 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	show_usage(void)
{
	ft_putendl("Usage: ./ft_otool [-f] <filename>");
	ft_putendl("options:");
	ft_putendl("-f: show all architectures contained in the universal binary");
}

static bool	set_flags(char const *argv_flags)
{
	while (*++argv_flags)
	{
		if (*argv_flags == 'f')
			toggle_fat_show_all_arch();
		else
			return (log_error(ERR_USAGE, "invalid flag", FROM));
	}
	return (true);
}

static bool	check_usage(int argc, char **argv, uint32_t *ptr_nb_of_files)
{
	int	i;

	i = 1;
	*ptr_nb_of_files = 0;
	while (i < argc)
	{
		if (argv[i] && *argv[i] == '-')
		{
			if (ft_strlen(argv[i]) <= 1 || !set_flags(argv[i]))
			{
				log_error(ERR_THROW, "flag usage is invalid", FROM);
				show_usage();
				return (false);
			}
		}
		else if (argv[i])
			(*ptr_nb_of_files)++;
		i++;
	}
	return (true);
}

int		main(int argc, char **argv)
{
	int			ret;
	uint32_t	nb_of_files;
	
	ret = 1;
	if (!check_usage(argc, argv, &nb_of_files))
	{
		log_error(ERR_THROW, "otool failure", FROM);
		return (EXIT_FAILURE);
	}
	while (*++argv)
	{
		if (**argv != '-')
		{
			if (nb_of_files > 1)
			{
				ft_putchar('\n');
				ft_putendl(*argv);
			}
			if (!machopera(*argv, &otool_conductor))
				ret = log_error(ERR_THROW, "otool failure", FROM);
		}
	}
	if (nb_of_files == 0 && !machopera(DEFAULT_TARGET, &otool_conductor))
		ret = log_error(ERR_THROW, "otool failure", FROM);
	return ((ret) ? EXIT_SUCCESS : EXIT_FAILURE);
}
