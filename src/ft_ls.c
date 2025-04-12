/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:19:40 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*extract_content(DIR *dir);
static t_list	*remove_ucontent(t_list *content, t_param para);
static t_list	*sort_content(t_list *content);
static bool		is_unwanted(char *content, t_param para);

void	ls_path(t_context ctx, char *path, char *arg)
{
	DIR			*dir;
	t_list		*content;

	dir = opendir(path);
	if (!dir)
	{
		ctx.code = MAJOR_ERROR;
		return (perror(ft_strjoin(ft_strjoin("ls: can't open directory '", arg), "'")));
	}
	if (ctx.multiple)
		ft_printf("%s:\n", arg);
	content = extract_content(dir);
	content = remove_ucontent(content, ctx.param);
	content = sort_content(content);
	print_content(content);
	if (!ctx.multiple)
		ft_printf("\n");
}

static t_list	*extract_content(DIR *dir)
{
	t_dirent	*dirent;
	t_list		*content;

	dirent = readdir_helper(dir);
	content = NULL;
	while (dirent)
	{
		ft_lstadd_back(&content, ft_lstnew(ft_strdup(dirent->d_name)));
		dirent = readdir_helper(dir);
	}
	closedir(dir);
	return (content);
}

static t_list	*remove_ucontent(t_list *content, t_param param)
{
	t_list	*prev;
	t_list	*mem;
	t_list	*del;

	prev = NULL;
	mem = content;
	while (content)
	{
		if (is_unwanted(content->content, param))
		{
			if (mem == content)
				mem = content->next;
			del = content;
			content = content->next;
			if (prev)
				prev->next = content;
			ft_lstdelone(del, free);
		}
		else
		{
			prev = content;
			content = content->next;
		}
	}
	return (mem);
}

static t_list	*sort_content(t_list *content)
{
	t_list	*mem;
	t_list	*swap;
	t_list	*prev;

	mem = content;
	prev = NULL;
	while (content->next)
	{
		if (ft_strcmp_casei(content->content, content->next->content) > 0)
		{
			if (mem == content)
				mem = content->next;
			if (prev)
				prev->next = content->next;
			swap = content->next->next;
			content->next->next = content;
			content->next = swap;
			content = mem;
			prev = NULL;
		}
		else
		{
			prev = content;
			content = content->next;
		}
	}
	return (mem);
}

static bool	is_unwanted(char *content, t_param param)
{
	if (!ft_strcmp(content, "..") || !ft_strcmp(content, "."))
		return (true);
	if (!param.hidden && !ft_strncmp(content, ".", 1))
		return (true);
	return (false);
}
