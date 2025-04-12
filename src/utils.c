/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:49:50 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 20:46:39 by ygille           ###   ########.fr       */
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