/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 12:38:18 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lslst	*extract_content(DIR *dir, t_context ctx);
static t_lslst	*sort_content(t_lslst *content, t_param param);
static void		get_subfolders(t_lslst *content, t_context ctx, char *upper);

/*
**	Get and print dir content from arg according to params
**	add found directories to list if in recursive mode
*/
void	ls_path(t_context ctx, char *arg)
{
	DIR			*dir;
	t_lslst	*content;
	int			size;

	size = 0;
	dir = opendir(arg);
	if (!dir)
	{
		ctx.code = MAJOR_ERROR;
		return (ft_perror(ELS_OPEN, arg));
	}
	if (ctx.multiple || ctx.param.recursive)
		ft_printf("%s:\n", arg);
	content = extract_content(dir, ctx);
	content = remove_ucontent(content, ctx.param);
	if (ctx.param.longformat || ctx.param.timesort)
		size = get_more_data(ctx, content, arg, ctx.param.longformat);
	content = sort_content(content, ctx.param);
	if (ctx.param.recursive)
		get_subfolders(content, ctx, arg);
	print_content(content, ctx.param, size);
	ft_lslstclear(&content, free);
	ft_printf("\n");
}

/*
**	Create a list of the content of dir
*/
static t_lslst	*extract_content(DIR *dir, t_context ctx)
{
	t_dirent	*dirent;
	t_lslst		*content;
	t_lslst		*node;
	char		*name;

	dirent = readdir_helper(dir);
	content = NULL;
	while (dirent)
	{
		name = mverif(ft_strdup(dirent->d_name));
		node = ft_lslstnew(name);
		ft_lslstadd_back(&content, node);
		node->mode = '-';
		if (ctx.param.recursive && dirent->d_type == DIRTYPE_DIR)
			node->mode = 'd';
		dirent = readdir_helper(dir);
	}
	closedir(dir);
	return (content);
}

static t_lslst	*sort_content(t_lslst *content, t_param param)
{
	if (!content)
		return (NULL);
	if (param.timesort)
		return (time_sort(content, param));
	return (alpha_sort(content, param));
}

/*
**	For recursive mode
*/
static void	get_subfolders(t_lslst *content, t_context ctx, char *upper)
{
	while (content)
	{
		if (content->mode == 'd')
			add_subfolder(ctx, content->name, upper);
		content = content->next;
	}
}
