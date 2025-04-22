/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:05:09 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 11:22:53 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	main(int argc, char **argv)
{
	t_context	ctx;

	ctx = parse_args(argc, argv);
	process_request(ctx);
	exit(ctx.code);
}

/*
**	Verify arguments paths and iter the list
**	files are shown first
*/
void	process_request(t_context ctx)
{
	t_list	*files;
	t_list	*directories;

	verif_paths(ctx.args, &ctx.files, &ctx.directories);
	files = ctx.files;
	directories = ctx.directories;
	if (files)
	{
		while (files)
		{
			ft_printf("%s  ", files->content);
			files = files->next;
		}
		ft_printf("\n\n");
	}
	ft_lstclear(&ctx.files, NULL);
	while (directories)
	{
		ls_path(ctx, directories->content);
		directories = directories->next;
	}
	ft_lstclear(&ctx.directories, free);
}
