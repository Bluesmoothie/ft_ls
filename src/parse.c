/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:11:12 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 14:37:38 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_option(t_param *param, char *option);
static void	parse_argument(t_list **lst, char *argument);

/*
**	Parse the argv, searching for options and arguments
*/
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
			parse_argument(&ctx.args, argv[i]);
		i++;
	}
	size = ft_lstsize(ctx.args);
	if (!size)
		parse_argument(&ctx.args, ".");
	else if (size > 1)
		ctx.multiple = true;
	return (ctx);
}

/*
**	Set param flag arcoding to option
*/
static void	parse_option(t_param *param, char *option)
{
	int	i;

	i = 1;
	while (option[i])
	{
		switch (option[i])
		{
			case	'l':
				param->longformat = true;
				break;
			case	'R':
				param->recursive = true;
				break;
			case	'a':
				param->hidden = true;
				break;
			case	'r':
				param->reverse = true;
				break;
			case	't':
				param->timesort = true;
				break;
			default:
				ft_printf("ft_ls: invalid option -- '%c'\n", option[i]);
				exit (-1);
		}
		i++;
	}
}

/*
**	Create a new node with the argument
*/
static void	parse_argument(t_list **lst, char *argument)
{
	t_list	*new;
	char	*arg;

	arg = mverif(ft_strdup(argument));
	new = ft_lstnew(arg);
	if (!new)
		exit(-1);
	ft_lstadd_back(lst, new);
}
