/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:49:50 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 12:24:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirent	*readdir_helper(DIR *dir)
{
	t_dirent	*dirent;

	errno = 0;
	dirent = readdir(dir);
	if (!dirent && errno)
		pexit();
	return (dirent);
}

int	ft_strcmp_casei(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}

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
