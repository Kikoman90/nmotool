/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:22:00 by fsidler           #+#    #+#             */
/*   Updated: 2019/02/14 19:22:09 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nmotool.h"

int		main(int argc, char **argv)
{
	if (argc < 2)
		printf("MAMENE MAMENE\n");
	else
	{
		while (argc--)
			printf("%s\n", argv[argc]);
	}	
	return (0);
}