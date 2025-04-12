/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:11:12 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:28:50 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	parse_option(t_param *param, char *option);
void	parse_argument(t_lslst **lst, char *argument);

t_context	parse_args(int argc, char **argv, char **envp)
{
	t_context ctx;
	int			i;
	int			size;

	ft_bzero(&ctx, sizeof(t_context));
	i = 1;
	while (i < argc)
	{
		if (!ft_strncmp(argv[i], "-", 1))
			parse_option(&ctx.param, argv[i]);
		else
			parse_argument(&ctx.lst, argv[i]);
		i++;
	}
	size = ft_lslstsize(ctx.lst);
	if (!size)
	{
		ctx.cwd = ft_getcwd(envp);
		ctx.cwd_mode = true;
	}
	else if (size > 1)
		ctx.multiple = true;
	return (ctx);
}

void	parse_option(t_param *param, char *option)
{
	int	i;

	i = 1;
	while (option[i])
	{
		if (option[i] == 'l')
			param->longformat = true;
		else if (option[i] == 'R')
			param->recursive = true;
		else if (option[i] == 'a')
			param->hidden = true;
		else if (option[i] == 'r')
			param->reverse = true;
		else if (option[i] == 't')
			param->timesort = true;
		i++;
	}
}

void	parse_argument(t_lslst **lst, char *argument)
{
	t_lslst	*new;

	new = ft_lslstnew(argument);
	if(!new)
		exit(-1);
	ft_lslstadd_back(lst, new);
}
