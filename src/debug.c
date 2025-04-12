/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:13:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:42:29 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_context(t_context ctx)
{
	ft_printf("Current context :\n\n");
	ft_printf("Options :\n");
	if (ctx.param.hidden)
		ft_printf("-a ");
	if (ctx.param.longformat)
		ft_printf("-l ");
	if (ctx.param.recursive)
		ft_printf("-R ");
	if (ctx.param.reverse)
		ft_printf("-r ");
	if (ctx.param.timesort)
		ft_printf("-t ");
	ft_printf("\n");
	if (!ctx.multiple)
		ft_printf("Unique argument detected\n\n");
	else
		ft_printf("Multiple arguments detected\n\n");
	if (ctx.cwd_mode)
	{
		ft_printf("Cwd mode detected on :\n");
		ft_printf("%s\n", ctx.cwd);
	}
	else
	{
		ft_printf("Arguments :\n");
		while (ctx.lst)
		{
			ft_printf("%s\n", ctx.lst->raw_arg);
			ctx.lst = ctx.lst->next;
		}
	}
	ft_printf("\nResult :\n_____\n");
}

void	print_lslst(t_lslst *lst)
{
	ft_printf("List content :\n");
	
}
