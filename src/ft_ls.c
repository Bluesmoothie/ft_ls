/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 00:50:46 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*extract_content(DIR *dir);
static t_list	*sort_content(t_list *content);
static int		sort_helper(const char *s1, const char *s2);

void	ls_path(t_context ctx, char *arg)
{
	DIR			*dir;
	t_list		*content;

	dir = opendir(arg);
	if (!dir)
	{
		ctx.code = MAJOR_ERROR;
		return (ft_perror(ELS_OPEN, arg));
	}
	if (ctx.multiple)
		ft_printf("%s:\n", arg);
	content = extract_content(dir);
	content = sort_content(content);
	print_content(content, ctx.param);
	ft_lstclear(&content, free);
	ft_printf("\n");
}

static t_list	*extract_content(DIR *dir)
{
	t_dirent	*dirent;
	t_list		*content;
	char		*name;

	dirent = readdir_helper(dir);
	content = NULL;
	while (dirent)
	{
		name = ft_strdup(dirent->d_name);
		mverif(name);
		ft_lstadd_back(&content, ft_lstnew(name));
		dirent = readdir_helper(dir);
	}
	closedir(dir);
	return (content);
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
		if (sort_helper(content->content, content->next->content) > 0)
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

static int	sort_helper(const char *s1, const char *s2)
{
	if (!ft_strncmp(s1, ".", 1) && s1[1])
		s1++;
	if (!ft_strncmp(s2, ".", 1)&& s2[1])
		s2++;
	return (ft_strcmp_casei(s1, s2));
}
