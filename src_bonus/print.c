/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:46:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 14:31:08 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_longformat(t_param param, t_lslst *content, int size);

void	print_content(t_lslst *content, t_param param, int size)
{
	if (param.longformat == SM_TRUE)
		return (print_longformat(param, content, size));
	while (content)
	{
		ft_printf("%s  ", content->name);
		content = content->next;
	}
}

static void	print_longformat(t_param param, t_lslst *content, int size)
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
		ft_printf("%c%s %s ", content->mode, content->perms, content->links);
		if (param.show_user)
			ft_printf("%s ", content->owner);
		if (param.show_group)
			ft_printf("%s ", content->group);
		ft_printf("%s %s %s", content->size, content->time, content->name);
		content = content->next;
	}
}
