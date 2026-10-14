/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:39:27 by ygille            #+#    #+#             */
/*   Updated: 2025/05/07 13:12:34 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	show_help(void);
static void	show_ver(void);

void	special_options(char *option)
{
	if (!ft_strcmp(option, "help"))
		show_help();
	else if (!ft_strcmp(option, "version"))
		show_ver();
	else
	{
		ft_printf("ft_ls: unrecognized option '--%s'\n", option);
		ft_printf("Try 'ft_ls --help' for more information.\n");
				exit (-1);
	}
	exit(0);
}

static void	show_help(void)
{
	ft_printf(HELP_MSG);
}

static void	show_ver(void)
{
	ft_printf(VER_MSG);
}
