/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/10 19:34:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	no_arg(char **envp);
static void	one_arg(char *arg);
static void	multiple_args(int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		no_arg(envp);
	else if (argc == 2)
		one_arg(argv[1]);
	else
		multiple_args(argc, argv);
	exit(0);
}

static void	no_arg(char **envp)
{
	char	*path;

	path = ft_getcwd(envp);
	if (verif_path(path))
		ls_path(path);
}

static void	one_arg(char *arg)
{
	char	*path;

	path = resolve_path(arg)
}

static void	multiple_args(int argc, char **argv)
{

}
