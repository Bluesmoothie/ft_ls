/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 23:42:36 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	no_arg(char **envp);
static void	one_arg(char *arg, char **envp);
static void	multiple_args(int argc, char **argv, char **envp);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		no_arg(envp);
	else if (argc == 2)
		one_arg(argv[1], envp);
	else
		multiple_args(argc, argv, envp);
	exit(0);
}

static void	no_arg(char **envp)
{
	char	*path;

	path = ft_getcwd(envp);
	if (verif_path(path, NULL))
		ls_path(path, NULL, false);
}

static void	one_arg(char *arg, char **envp)
{
	char	*path;

	path = resolve_path(arg, envp);
	if (verif_path(path, arg))
		ls_path(path, arg, false);
}

static void	multiple_args(int argc, char **argv, char **envp)
{
	char	**valid_paths;
	char	**args;
	char	*path;
	int		i;
	int		j;

	i = 1;
	j = 0;
	valid_paths = ft_calloc(sizeof(char *), argc);
	args = ft_calloc(sizeof(char *), argc);
	if (!valid_paths || !args)
		exit(-1);
	while (i < argc)
	{
		path = resolve_path(argv[i], envp);
		if (verif_path(path, argv[i++]))
		{
			valid_paths[j] = path;
			args[j++] = argv[i - 1];
		}
	}
	i = -1;
	while (valid_paths[++i])
		ls_path(valid_paths[i], args[i], true);
}
