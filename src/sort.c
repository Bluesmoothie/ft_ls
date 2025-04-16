/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:45:34 by ygille            #+#    #+#             */
/*   Updated: 2025/04/16 11:54:14 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool		sort_helper(const char *s1, const char *s2, t_param param);
static void		swaper(t_lslst2 **prev, t_lslst2 **content);
static bool		time_sort_helper(t_lslst2 *c1, t_lslst2 *c2, t_param param);

t_lslst2	*time_sort(t_lslst2 *content, t_param param)
{
	t_lslst2	*mem;
	t_lslst2	*swap;
	t_lslst2	*prev;

	mem = content;
	prev = NULL;
	while (content->next)
	{
		if (time_sort_helper(content, content->next, param))
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

t_lslst2	*alpha_sort(t_lslst2 *content, t_param param)
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

static bool	time_sort_helper(t_lslst2 *c1, t_lslst2 *c2, t_param param)
{
	bool	result;

	result = false;
	if (c1->mtime.tv_sec == c2->mtime.tv_sec && c1->mtime.tv_nsec == c2->mtime.tv_nsec)
		return (sort_helper(c1->name, c2->name, param));
	if ((c1->mtime.tv_sec == c2->mtime.tv_sec && c1->mtime.tv_nsec < c2->mtime.tv_nsec) || c1->mtime.tv_sec < c2->mtime.tv_sec)
		result = true;
	if (param.reverse)
		return (!result);
	else
		return (result);
}
