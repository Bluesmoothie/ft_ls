/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 23:54:36 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_path(char *path, char *arg, bool mul)
{
	DIR			*dir;
	t_dirent	*dirent;

	// ft_printf("ls_path = %s\n", path);
	dir = opendir(path);
	if (!dir)
		return (perror(ft_strjoin(ft_strjoin("ls: can't open directory '", arg), "'")));
	if (mul)
		ft_printf("%s:\n", arg);
	errno = 0;
	dirent = readdir(dir);
	if (!dirent && errno)
		return (perror(NULL));
	while (dirent)
	{
		ft_printf("%s ", dirent->d_name);
		errno = 0;
		dirent = readdir(dir);
		if (!dirent && errno)
			return (perror(NULL));
	}
	ft_printf("\n\n");
}
