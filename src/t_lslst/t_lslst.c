/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lslst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:03:46 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 11:15:00 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_lslst.h"

/*
** Allocate a new node, initialize it's name to name
** returning it's adress or NULL on error
*/
t_lslst	*ft_lslstnew(char *name)
{
	t_lslst	*new;

	new = ft_calloc (1, sizeof(t_lslst));
	if (new != NULL)
		new->name = name;
	return (new);
}

/*
** Add a node new at the end of the list lst
** updating the lst pointer
*/
void	ft_lslstadd_back(t_lslst **lst, t_lslst *new)
{
	t_lslst	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lslstlast(*lst);
	last->next = new;
}

/*
** Return the pointer to the last node of lst
*/
t_lslst	*ft_lslstlast(t_lslst *lst)
{
	if (lst != NULL)
		while (lst->next != NULL)
			lst = lst->next;
	return (lst);
}

/*
** Return the size of lst
*/
int	ft_lslstsize(t_lslst *lst)
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
void	ft_lslstclear(t_lslst **lst, void (*del)(void*))
{
	t_lslst	*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		ft_lslstdelone(*lst, del);
		*lst = tmp;
	}
}
