/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:45:34 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 19:19:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_lslst2	*time_sort(t_lslst2 *content);
static t_lslst2	*alpha_sort(t_lslst2 *content, t_param param);
static bool		sort_helper(const char *s1, const char *s2, t_param param);
static void		swaper(t_lslst2 **prev, t_lslst2 **content);

t_lslst2	*sort_content(t_lslst2 *content, t_param param)
{
	if (param.timesort)
		return (time_sort(content));
	return (alpha_sort(content, param));
}

static t_lslst2	*time_sort(t_lslst2 *content)
{
	t_lslst2	*mem;
	t_lslst2	*swap;
	t_lslst2	*prev;

	mem = content;
	prev = NULL;
	while (content->next)
	{
		if ((content->timev < content->next->timev))
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

static t_lslst2	*alpha_sort(t_lslst2 *content, t_param param)
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
