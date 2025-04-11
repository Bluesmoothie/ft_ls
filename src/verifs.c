/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:40:06 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 23:40:30 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool	verif_path(char *path, char *arg)
{
	t_stat	path_stat;

	// ft_printf("verif_path = %s\n", path);
	if (stat(path, &path_stat) == -1)
	{
		perror(ft_strjoin(ft_strjoin("ls: can't access '", arg), "'"));
		return (false);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}
