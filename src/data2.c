/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:39:20 by ygille            #+#    #+#             */
/*   Updated: 2025/04/16 12:22:46 by ygille           ###   ########.fr       */
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

char	*normal_time(char *src)
{
	char	*time_str;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	while (src[start] != ' ')
		start++;
	while (src[end] != ':')
		end++;
	end += 3;
	time_str = ft_substr(src, start, end - start);
	return (mverif(time_str));
}

char	*old_time(char *src)
{
	char	*tmp[2];
	char	*time_str;
	char	*year;
	size_t	start;
	size_t	end;

	year = ft_substr(src, ft_strlen(src) - 6, 5);
	mverif(year);
	start = 0;
	end = 0;
	while (src[start] != ' ')
		start++;
	while (src[end] != ':')
		end++;
	end -= 2;
	time_str = ft_substr(src, start, end - start);
	tmp[0] = time_str;
	tmp[1] = year;
	time_str = ft_strjoin(time_str, year);
	free (tmp[0]);
	free (tmp[1]);
	return (mverif(time_str));
}
