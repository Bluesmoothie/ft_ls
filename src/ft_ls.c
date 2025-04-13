/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 21:03:34 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lslst2	*extract_content(DIR *dir);
static t_lslst2	*sort_content(t_lslst2 *content, t_param param);
static bool		sort_helper(const char *s1, const char *s2, t_param param);
static void		swaper(t_lslst2 **prev, t_lslst2 **content);

void	ls_path(t_context ctx, char *arg)
{
	DIR			*dir;
	t_lslst2	*content;

	dir = opendir(arg);
	if (!dir)
	{
		ctx.code = MAJOR_ERROR;
		return (ft_perror(ELS_OPEN, arg));
	}
	if (ctx.multiple)
		ft_printf("%s:\n", arg);
	content = extract_content(dir);
	content = sort_content(content, ctx.param);
	if (ctx.param.timesort || ctx.param.longformat)
		get_file_time(content);
	if (ctx.param.longformat)
		get_more_data(content, arg);
	print_content(content, ctx.param);
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
	t_lslst2	*mem;
	t_lslst2	*swap;
	t_lslst2	*prev;

	mem = content;
	prev = NULL;
	while (content->next)
	{
		if (sort_helper(content->name, content->next->name, param))
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
			swaper(&prev, &content);
	}
	return (mem);
}

static bool	sort_helper(const char *s1, const char *s2, t_param param)
{
	if (param.reverse && !ft_strcmp(s1, ".") && !ft_strcmp(s2, ".."))
		return (true);
	if (!ft_strncmp(s1, ".", 1) && s1[1])
		s1++;
	if (!ft_strncmp(s2, ".", 1) && s2[1])
		s2++;
	if (!param.reverse && ft_strcmp_casei(s1, s2) > 0)
		return (true);
	else if (param.reverse && ft_strcmp_casei(s1, s2) < 0)
		return (true);
	return (false);
}

static void	swaper(t_lslst2 **prev, t_lslst2 **content)
{
	*prev = *content;
	*content = (*content)->next;
}
