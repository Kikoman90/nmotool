/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:21:53 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/09 10:15:39 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	show_usage(void)
{
	ft_putendl("Usage: ./ft_nm [-agjnrpuU] <filename>");
	ft_putendl("options:");
	ft_putendl("-a: display all symbol table entries");
	ft_putendl("-g: display only external symbols");
	ft_putendl("-j: only display symbol names");
	ft_putendl("-n: sort symbols numerically (by address)");
	ft_putendl("-r: sort symbols in reverse order");
	ft_putendl("-p: don't sort; display in symbol table order");
	ft_putendl("-u: display only undefined symbols");
	ft_putendl("-U: don't display undefined symbols");
}

static bool	set_flags(char const *argv_flags)
{
	if (!(*argv_flags++))
		return (log_error(ERR_USAGE, "no flag", FROM));
	while (*argv_flags)
	{
		if (*argv_flags == 'a')
			toggle_print_flag(FLAG_a);
		else if (*argv_flags == 'g')
			toggle_print_flag(FLAG_g);
		else if (*argv_flags == 'j')
			toggle_print_flag(FLAG_j);
		else if (*argv_flags == 'n')
			toggle_sort_flag(FLAG_n);
		else if (*argv_flags == 'r')
			toggle_sort_flag(FLAG_r);
		else if (*argv_flags == 'p')
			toggle_sort_flag(FLAG_p);
		else if (*argv_flags == 'u')
			toggle_print_flag(FLAG_u);
		else if (*argv_flags == 'U')
			toggle_print_flag(FLAG_U);
		else
			return (log_error(ERR_USAGE, "invalid flag", FROM));
		argv_flags++;
	}
	return (true);
}

static bool	check_argv(int argc, char **argv, size_t *ptr_nb_of_files)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (*argv[i] == '-')
		{
			if (!set_flags(argv[i]))
			{
				show_usage();
				return (log_error(ERR_THROW, "could not set nm flags", FROM));
			}
		}
		else
			(*ptr_nb_of_files)++;
		i++;
	}
	return (true);
}

int			main(int argc, char **argv)
{
	int		ret;
	size_t	nb_of_files;

	ret = 1;
	if (!check_argv(argc, argv, &nb_of_files))
	{
		log_error(ERR_THROW, "nm failure", FROM);
		return (EXIT_FAILURE);
	}
	while (*++argv)
	{
		if (**argv != '-')
		{
			if (nb_of_files > 1)
			{
				ft_putchar('\n');
				ft_putstr(*argv);
				ft_putstr(":\n");
			}
			if (!machopera(*argv, &nm_conductor))
				ret = log_error(ERR_THROW, "nm failure", FROM);
		}
	}
	if (nb_of_files == 0 && !machopera(DEFAULT_TARGET, &nm_conductor))
		ret = log_error(ERR_THROW, "nm failure", FROM);
	return ((ret) ? EXIT_SUCCESS : EXIT_FAILURE);
}