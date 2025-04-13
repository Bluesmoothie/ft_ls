/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 20:54:03 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool	file_listed(t_lslst *lst);

int	main(int argc, char **argv, char **envp)
{
	t_context	ctx;

	ctx = parse_args(argc, argv, envp);
	process_request(ctx);
	ft_lslstclear(&ctx.lst, free);
	if (ctx.cwd)
		free(ctx.cwd);
	exit(ctx.code);
}

void	process_request(t_context ctx)
{
	t_lslst	*lst;

	if (ctx.cwd_mode)
		return (ls_path(ctx, ctx.cwd));
	verif_paths(ctx.lst);
	lst = ctx.lst;
	while (lst)
	{
		if (lst->mode == MLS_FILE)
			ft_printf("%s  ", lst->raw_arg);
		lst = lst->next;
	}
	lst = ctx.lst;
	if (file_listed(lst))
		ft_printf("\n\n");
	while (lst)
	{
		if (lst->mode == MLS_DIRECTORY)
		{
			ls_path(ctx, lst->raw_arg);
			ft_printf("\n");
		}
		lst = lst->next;
	}
}

static bool	file_listed(t_lslst *lst)
{
	while (lst)
	{
		if (lst->mode == MLS_FILE)
			return (true);
		lst = lst->next;
	}
	return (false);
}
