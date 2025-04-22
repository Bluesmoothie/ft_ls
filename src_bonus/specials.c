/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:27 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 14:45:07 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	show_help(void);

void	special_options(char *option)
{
	if (!ft_strcmp(option, "help"))
	{
		show_help();
		exit (0);
	}
	else
	{
		ft_printf("ft_ls: unrecognized option '--%s'\n", option);
		ft_printf("Try 'ft_ls --help' for more information.\n");
				exit (-1);
	}
}

static void	show_help(void)
{
	
}
