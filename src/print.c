/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:46:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 00:40:37 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static bool		is_unwanted(char *content, t_param para);

void	print_content(t_list *content, t_param param)
{
	while (content)
	{
		if (!is_unwanted(content->content, param))
			ft_printf("%s  ", content->content);
		content = content->next;
	}
}

static bool	is_unwanted(char *content, t_param param)
{
	if (!param.hidden && !ft_strncmp(content, ".", 1))
		return (true);
	return (false);
}
