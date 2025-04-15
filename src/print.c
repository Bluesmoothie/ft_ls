/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:46:45 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 17:43:42 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_longformat(t_lslst2 *content, int size);
static char		*time_helper(time_t time);

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
	char	*time;

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
		time = time_helper(content->time);
		ft_printf("%c%s %d %s %s %d %s %s", content->mode, content->perms,
			content->links, content->owner, content->group, content->size,
			time, content->name);
		free(time);
		content = content->next;
	}
}

static char	*time_helper(time_t time)
{
	char	*time_str;
	char	*tmp;
	size_t	start;
	size_t	end;

	tmp = ctime(&time);
	mverif(tmp);
	start = 0;
	end = 0;
	while (tmp[start] != ' ')
		start++;
	while (tmp[end] != ':')
		end++;
	end += 3;
	time_str = ft_substr(tmp, start, end - start);
	mverif(time_str);
	return (time_str);
}
