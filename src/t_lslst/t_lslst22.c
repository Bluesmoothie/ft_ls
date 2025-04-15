/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst22.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:08:50 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 18:09:43 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lslst2.h"

/*
** Delte one node at lst using del
*/
void	ft_lslst2delone(t_lslst2 *lst, void (*del)(void*))
{
	if (lst != NULL)
	{
		if (lst->name)
			del(lst->name);
		if (lst->group)
			del(lst->group);
		if (lst->owner)
			del(lst->owner);
		if (lst->size)
			del(lst->size);
		if (lst->time)
			del(lst->time);
		if (lst->links)
			del(lst->links);
		free(lst);
	}
}
