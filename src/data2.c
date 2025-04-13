/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:20 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 20:46:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*get_owner(int uid)
{
	t_passwd	*data;

	data = getpwuid(uid);
	return (ft_strdup(data->pw_name));
}

char	*get_group(int gid)
{
	t_group	*data;

	data = getgrgid(gid);
	return (ft_strdup(data->gr_name));
}