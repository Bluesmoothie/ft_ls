/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/16 11:34:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lslst2	*extract_content(DIR *dir);
static t_lslst2	*sort_content(t_lslst2 *content, t_param param);

void	ls_path(t_context ctx, char *arg)
{
	DIR			*dir;
	t_lslst2	*content;
	int			size;

	size = 0;
	dir = opendir(arg);
	if (!dir)
	{
		ctx.code = MAJOR_ERROR;
		return (ft_perror(ELS_OPEN, arg));
	}
	if (ctx.multiple)
		ft_printf("%s:\n", arg);
	content = extract_content(dir);
	content = remove_ucontent(content, ctx.param);
	if (ctx.param.longformat || ctx.param.timesort)
		size = get_more_data(content, arg, ctx.param.longformat);
	content = sort_content(content, ctx.param);
	print_content(content, ctx.param, size);
	ft_lslst2clear(&content, free);
	ft_printf("\n");
}

static t_lslst2	*extract_content(DIR *dir)
{
	t_dirent	*dirent;
	t_lslst2	*content;
	char		*name;

	dirent = readdir_helper(dir);
	content = NULL;
	while (dirent)
	{
		name = ft_strdup(dirent->d_name);
		mverif(name);
		ft_lslst2add_back(&content, ft_lslst2new(name));
		dirent = readdir_helper(dir);
	}
	closedir(dir);
	return (content);
}

static t_lslst2	*sort_content(t_lslst2 *content, t_param param)
{
	if (param.timesort)
		return (time_sort(content, param));
	return (alpha_sort(content, param));
}
