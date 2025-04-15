/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:10:43 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 18:43:12 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_align_sizes	calc_max(t_lslst2 *content);
static t_align_sizes	calc_sizes(t_lslst2 *node);
static t_align_sizes	as_max(t_align_sizes as1, t_align_sizes as2);
static char				*resize_to(char *src, size_t size, size_t src_size);

void	align_data(t_lslst2 *content)
{
	t_align_sizes	max;

	max = calc_max(content);
	while (content)
	{
		content->group = resize_to(content->group, max.group, content->sizes.group);
		content->links = resize_to(content->links, max.links, content->sizes.links);
		content->owner = resize_to(content->owner, max.owner, content->sizes.owner);
		content->size = resize_to(content->size, max.size, content->sizes.size);
		content->time = resize_to(content->time, max.time, content->sizes.time);
		content = content->next;
	}
}

static t_align_sizes	calc_max(t_lslst2 *content)
{
	t_align_sizes	max;
	t_align_sizes	as;

	ft_bzero(&max, sizeof(t_align_sizes));
	while (content)
	{
		as = calc_sizes(content);
		max = as_max(as, max);
		content = content->next;
	}
	return (max);
}

static t_align_sizes	calc_sizes(t_lslst2 *node)
{
	node->sizes.group = ft_strlen(node->group);
	node->sizes.links = ft_strlen(node->links);
	node->sizes.owner = ft_strlen(node->owner);
	node->sizes.size = ft_strlen(node->size);
	node->sizes.time = ft_strlen(node->time);
	return (node->sizes);
}

static t_align_sizes	as_max(t_align_sizes as1, t_align_sizes as2)
{
	if (as2.group > as1.group)
		as1.group = as2.group;
	if (as2.links > as1.links)
		as1.links = as2.links;
	if (as2.owner > as1.owner)
		as1.owner = as2.owner;
	if (as2.size > as1.size)
		as1.size = as2.size;
	if (as2.time > as1.time)
		as1.time = as2.time;
	return (as1);
}

static char	*resize_to(char *src, size_t size, size_t src_size)
{
	char	*result;

	if (size == src_size)
		return (src);
	result = malloc(sizeof(char) * (size + 1));
	mverif(result);
	ft_memset(result, ' ', size - src_size);
	ft_memcpy(&result[size - src_size], src, src_size + 1);
	free(src);
	return (result);
}
