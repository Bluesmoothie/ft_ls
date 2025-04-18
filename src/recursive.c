/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:06:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/18 20:20:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	add_subfolder(t_context ctx, char *name, char *upper)
{
	t_lslst	*new;
	char	*path;
	char	*tmp;

	if (!ft_strcmp(name, ".") || !ft_strcmp(name, "..")
		|| (!ctx.param.hidden && !ft_strncmp(name, ".", 1)))
		return ;
	if (ft_strncmp(&upper[ft_strlen(upper) - 1], "/", 1))
	{
		tmp = mverif(ft_strjoin(upper, "/"));
		path = mverif(ft_strjoin(tmp, name));
		free(tmp);
	}
	else
		path = mverif(ft_strjoin(upper, name));
	new = ft_lslstnew(path);
	if (!new)
		exit(-1);
	new->mode = MLS_DIRECTORY;
	ft_lslstadd_back(&ctx.lst, new);
}
