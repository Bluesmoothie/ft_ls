/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:35:41 by ygille            #+#    #+#             */
/*   Updated: 2025/04/17 18:41:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_option(t_param *param, char *option);
static void	parse_argument(t_lslst **lst, char *argument);

t_context	parse_args(int argc, char **argv)
{
	t_context	ctx;
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
		parse_argument(&ctx.lst, ".");
	else if (size > 1)
		ctx.multiple = true;
	return (ctx);
}

static void	parse_option(t_param *param, char *option)
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
		else if (option[i] == 'u')
			param->atimesort = true;
		else if (option[i] == 'f')
			param->unsorted = true;
		else if (option[i] == 'g')
			param->noowner = true;
		else if (option[i] == 'd')
			param->listdirectories = true;
		i++;
	}
}

static void	parse_argument(t_lslst **lst, char *argument)
{
	t_lslst	*new;
	char	*name;

	name = mverif(ft_strdup(argument));
	new = ft_lslstnew(name);
	if (!new)
		exit(-1);
	ft_lslstadd_back(lst, new);
}
