/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 11:40:30 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_subfolder(t_context ctx, char *name, char *upper)
{
	t_list	*new;
	char	*path;
	char	*tmp;

	if (!ft_strcmp(name, ".") || !ft_strcmp(name, "..")
		|| (!ctx.param.hidden && !ft_strncmp(name, ".", 1)))
		return ;
	tmp = mverif(ft_strjoin(upper, "/"));
	path = mverif(ft_strjoin(tmp, name));
	free(tmp);
	new = ft_lstnew(path);
	if (!new)
		exit(-1);
	ft_lstadd_back(&ctx.directories, new);
}
