/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:04:57 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 14:11:05 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool	is_unwanted(char *content, t_param para);

t_lslst2	*remove_ucontent(t_lslst2 *content, t_param param)
{
	t_lslst2	*prev;
	t_lslst2	*mem;
	t_lslst2	*del;

	prev = NULL;
	mem = content;
	while (content)
	{
		if (is_unwanted(content->name, param))
		{
			if (mem == content)
				mem = content->next;
			del = content;
			content = content->next;
			if (prev)
				prev->next = content;
			ft_lslst2delone(del, free);
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
	if (!param.hidden && !ft_strncmp(content, ".", 1))
		return (true);
	return (false);
}
