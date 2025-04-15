/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:47:43 by ygille            #+#    #+#             */
/*   Updated: 2025/04/15 16:10:33 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_data(t_lslst2 *content, char *path);
static char	get_mode(t_stat data);
static void	get_perms(t_stat data, t_lslst2 *content);

int	get_more_data(t_lslst2 *content, char *path)
{
	char	*fpath;
	int		size;

	path = ft_strjoin(path, "/");
	size = 0;
	mverif(path);
	while (content)
	{
		fpath = ft_strjoin(path, content->name);
		mverif(path);
		size += fill_data(content, fpath);
		free(fpath);
		content = content->next;
	}
	free(path);
	return (size / 2);
}

static int	fill_data(t_lslst2 *content, char *path)
{
	t_stat	data;

	stat(path, &data);
	content->mode = get_mode(data);
	get_perms(data, content);
	content->links = data.st_nlink;
	content->owner = get_owner(data.st_uid);
	content->group = get_group(data.st_gid);
	content->size = data.st_size;
	content->time = data.st_mtime;
	return (data.st_blocks);
}

static char	get_mode(t_stat data)
{
	if (S_ISREG(data.st_mode))
		return (MLS2_FILE);
	if (S_ISDIR(data.st_mode))
		return (MLS2_DIR);
	if (S_ISLNK(data.st_mode))
		return (MLS2_LNK);
	return (MLS2_INVALID);
}

static void	get_perms(t_stat data, t_lslst2 *content)
{
	ft_memset(&content->perms, '-', 9);
	content->perms[9] = '\0';
	if (S_IRUSR & data.st_mode)
		content->perms[0] = 'r';
	if (S_IWUSR & data.st_mode)
		content->perms[1] = 'w';
	if (S_IXUSR & data.st_mode)
		content->perms[2] = 'x';
	if (S_IRGRP & data.st_mode)
		content->perms[3] = 'r';
	if (S_IWGRP & data.st_mode)
		content->perms[4] = 'w';
	if (S_IXGRP & data.st_mode)
		content->perms[5] = 'x';
	if (S_IROTH & data.st_mode)
		content->perms[6] = 'r';
	if (S_IWOTH & data.st_mode)
		content->perms[7] = 'w';
	if (S_IXOTH & data.st_mode)
		content->perms[8] = 'x';
}
