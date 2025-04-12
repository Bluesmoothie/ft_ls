/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 21:00:45 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	no_arg(char **envp, t_param param);
static void	one_arg(char *arg, char **envp, t_param param);
static void	multiple_args(int argc, char **argv, char **envp, t_param param);
static void	ls_mpath(char **paths, char **args, t_param param);

int	main(int argc, char **argv, char **envp)
{
	t_param	param;

	ft_bzero(&param, sizeof(t_param));
	if (argc == 1)
		no_arg(envp, param);
	else if (argc == 2)
		one_arg(argv[1], envp, param);
	else
		multiple_args(argc, argv, envp, param);
	exit(0);
}

static void	no_arg(char **envp, t_param param)
{
	char	*path;

	path = ft_getcwd(envp);
	if (verif_path(path, NULL))
		ls_path(path, NULL, false, param);
}

static void	one_arg(char *arg, char **envp, t_param param)
{
	char	*path;

	path = resolve_path(arg, envp);
	if (verif_path(path, arg))
		ls_path(path, arg, false, param);
}

static void	multiple_args(int argc, char **argv, char **envp, t_param param)
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
	ls_mpath(valid_paths, args, param);
}

static void	ls_mpath(char **paths, char **args, t_param param)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		if(ls_path(paths[i], args[i], true, param))
			ft_printf("\n");
		i++;
	}
}