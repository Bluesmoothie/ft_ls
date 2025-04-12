/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:40:06 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:38:14 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	verif_paths(t_lslst *lst)
{
	t_stat	path_stat;

	while (lst)
	{
		lst->mode = MLS_INVALID;
		if (stat(lst->raw_arg, &path_stat) == -1)
			perror(ft_strjoin(ft_strjoin("ls: can't access '", lst->raw_arg), "'"));
		else if (S_ISDIR(path_stat.st_mode))
			lst->mode = MLS_DIRECTORY;
		else if (S_ISREG(path_stat.st_mode))
			lst->mode = MLS_FILE;
		lst = lst->next;
	}
}
