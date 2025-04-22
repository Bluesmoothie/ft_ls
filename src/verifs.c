/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:40:06 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 10:54:32 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Separate lst into to lists, one for files and one for directories
**	print an error if a path is invalid
*/
void	verif_paths(t_list *lst, t_list **files, t_list **directories)
{
	t_stat	path_stat;
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (stat(lst->content, &path_stat) == -1)
			ft_perror(ELS_ACCESS, lst->content);
		else if (S_ISDIR(path_stat.st_mode))
		{
			lst->next = NULL;
			ft_lstadd_back(directories, lst);
		}
		else if (S_ISREG(path_stat.st_mode))
		{
			lst->next = NULL;
			ft_lstadd_back(files, lst);
		}
		lst = tmp;
	}
}
