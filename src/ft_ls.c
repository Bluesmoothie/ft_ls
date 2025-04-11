/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:10:17 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 23:41:37 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_path(char *path, char *arg, bool mul)
{
	DIR		*dir;

	// ft_printf("ls_path = %s\n", path);
	dir = opendir(path);
	if (!dir)
		return (perror(ft_strjoin(ft_strjoin("ls: can't open directory '", arg), "'")));
	if (mul)
		ft_printf("%s:\n", arg);
}
