/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:46:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 21:00:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool		is_unwanted(char *content, t_param para);
static void		print_longformat(t_lslst2 *content, t_param param);

void	print_content(t_lslst2 *content, t_param param)
{
	if (param.longformat)
		return (print_longformat(content, param));
	while (content)
	{
		if (!is_unwanted(content->name, param))
			ft_printf("%s  ", content->name);
		content = content->next;
	}
}

static bool	is_unwanted(char *content, t_param param)
{
	if (!param.hidden && !ft_strncmp(content, ".", 1))
		return (true);
	return (false);
}

static void	print_longformat(t_lslst2 *content, t_param param)
{
	bool	first;

	first = true;
	while (content)
	{
		if (!is_unwanted(content->name, param))
		{
			if (!first)
				ft_printf("\n");
			else
				first = false;
			ft_printf("%c%s %d %s %s %d %s", content->mode, content->perms,
				content->links, content->owner, content->group, content->size,
				content->name);
		}
		content = content->next;
	}
}
