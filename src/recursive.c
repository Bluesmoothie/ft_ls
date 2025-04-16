/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/16 14:37:14 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_subfolder(t_context ctx, char *name)
{
	t_lslst	*new;

	if (!ft_strcmp(name, ".") || !ft_strcmp(name, "..") || (!ctx.param.hidden && !ft_strncmp(name, ".", 1)))
		return ;
	new = ft_lslstnew(name);
	if (!new)
		exit(-1);
	new->mode = MLS_DIRECTORY;
	ft_lslstadd_back(&ctx.lst, new);
}
