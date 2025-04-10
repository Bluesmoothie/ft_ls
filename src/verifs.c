/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verifs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:40:06 by ygille            #+#    #+#             */
/*   Updated: 2025/04/10 18:52:34 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool	verif_path(char *path)
{
	t_stat	path_stat;

	if (stat(path, &path_stat) == -1)
		perror(NULL);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}
