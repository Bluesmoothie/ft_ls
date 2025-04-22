/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:35:41 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 14:45:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_option(t_param *param, char *option);
static void	parse_argument(t_list **lst, char *argument);
static void	complete_options(t_param *param);
static void	set_base_param(t_param *param);

/*
**	Parse the argv, searching for options and arguments
*/
t_context	parse_args(int argc, char **argv)
{
	t_context	ctx;
	int			i;
	int			size;

	ft_bzero(&ctx, sizeof(t_context));
	set_base_param(&ctx.param);
	i = 1;
	while (i < argc)
	{
		if (!ft_strncmp(argv[i], "-", 1))
			parse_option(&ctx.param, argv[i]);
		else
			parse_argument(&ctx.args, argv[i]);
		i++;
	}
	complete_options(&ctx.param);
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
				if (param->longformat == SM_FALSE)
					param->longformat = SM_TRUE;
				break;
			case	'R':
				param->recursive = true;
				break;
			case	'a':
				param->hidden = true;
				break;
			case	'r':
				if (param->reverse == SM_FALSE)
					param->reverse = SM_TRUE;
				break;
			case	't':
				if (param->timesort == SM_FALSE)
					param->timesort = SM_TRUE;
				break;
			case	'u':
				param->time_mode = TM_ACCESS;
				break;
			case	'f':
				param->hidden = true;
				param->sort = false;
				param->timesort = SM_BLOCKED;
				param->color = SM_BLOCKED;
				param->reverse = SM_BLOCKED;
				break;
			case	'U':
				param->sort = false;
				break;
			case	'c':
				param->time_mode = TM_CREATE;
				break;
			case	'g':
				param->show_user = false;
				if (param->longformat == SM_FALSE)
					param->longformat = SM_TRUE;
				break;
			case	'o':
				param->show_group = false;
				if (param->longformat == SM_FALSE)
					param->longformat = SM_TRUE;
				break;
			case	'-':
				if (i == 1)
					special_options(&option[2]);
			default:
				ft_printf("ft_ls: invalid option -- '%c'\n", option[i]);
				ft_printf("Try 'ft_ls --help' for more information.\n");
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

static void	complete_options(t_param *param)
{
	if (!param->longformat && param->time_mode)
		param->timesort = true;
}

static void	set_base_param(t_param *param)
{
	param->sort = true;
	param->show_group = true;
	param->show_user = true;
}
