/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:46:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 14:12:58 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_longformat(t_lslst2 *content, int size);

void	print_content(t_lslst2 *content, t_param param, int size)
{
	if (param.longformat)
		return (print_longformat(content, size));
	while (content)
	{
		ft_printf("%s  ", content->name);
		content = content->next;
	}
}

static void	print_longformat(t_lslst2 *content, int size)
{
	bool	first;

	first = true;
	while (content)
	{
		if (!first)
			ft_printf("\n");
		else
		{
			first = false;
			ft_printf("total %d\n", size);
		}
		ft_printf("%c%s %d %s %s %d %s", content->mode, content->perms,
			content->links, content->owner, content->group, content->size,
			content->name);
		content = content->next;
	}
}
