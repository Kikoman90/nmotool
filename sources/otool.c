/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <fsidler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:22:00 by fsidler           #+#    #+#             */
/*   Updated: 2019/06/07 14:45:36 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

//
#include <stdio.h>
//

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
