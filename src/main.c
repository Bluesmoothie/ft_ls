/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:41:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	ctx;

	ctx = parse_args(argc, argv, envp);
	// print_context(ctx);
	process_request(ctx);
	exit(ctx.code);
}

void	process_request(t_context ctx)
{
	if (ctx.cwd_mode)
		return (ls_path(ctx, ctx.cwd, ctx.cwd));
	verif_paths(ctx.lst);
	print_lslst(ctx.lst);
}
