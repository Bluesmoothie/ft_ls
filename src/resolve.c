/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:46:36 by ygille            #+#    #+#             */
/*   Updated: 2025/04/11 22:57:02 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*resolve_path(char *arg, char **envp)
{
	if (!ft_strncmp(arg, "/", 1))
		return (arg);
	else
		return (ft_strjoin(ft_strjoin(ft_getcwd(envp), "/"), arg));
}
