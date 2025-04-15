/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:46 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 14:12:30 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lslst2.h"

/*
** Allocate a new node, initialize it's name to name
** returning it's adress or NULL on error
*/
t_lslst2	*ft_lslst2new(char *name)
{
	t_lslst2	*new;

	new = malloc (sizeof(t_lslst2));
	if (new != NULL)
	{
		new->name = name;
		new->next = NULL;
	}
	return (new);
}

/*
** Add a node new at the end of the list lst
** updating the lst pointer
*/
void	ft_lslst2add_back(t_lslst2 **lst, t_lslst2 *new)
{
	t_lslst2	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lslst2last(*lst);
	last->next = new;
}

/*
** Return the pointer to the last node of lst
*/
t_lslst2	*ft_lslst2last(t_lslst2 *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

/*
** Return the size of lst
*/
int	ft_lslst2size(t_lslst2 *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

/*
** Use del function to delete all nodes
** in lst, updating the pointer
*/
void	ft_lslst2clear(t_lslst2 **lst, void (*del)(void*))
{
	t_lslst2	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lslst2delone(*lst, del);
		*lst = tmp;
	}
}
