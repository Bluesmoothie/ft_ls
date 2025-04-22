/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:47:43 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 13:00:16 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	fill_data(t_context ctx, t_lslst *content, char *path, bool moremore);
static char	get_mode(t_stat data);
static void	get_perms(t_stat data, t_lslst *content);
static char	*time_helper(time_t ftime);

/*
**	Get more data for longformat output
*/
int	get_more_data(t_context ctx, t_lslst *content, char *path, bool moremore)
{
	t_lslst	*lst;
	char		*fpath;
	int			size;

	lst = content;
	path = ft_strjoin(path, "/");
	size = 0;
	mverif(path);
	while (content)
	{
		fpath = ft_strjoin(path, content->name);
		mverif(path);
		size += fill_data(ctx, content, fpath, moremore);
		free(fpath);
		content = content->next;
	}
	free(path);
	align_data(lst);
	return (size / 2);
}

static int	fill_data(t_context ctx, t_lslst *content, char *path, bool moremore)
{
	t_stat	data;

	stat(path, &data);
	if (moremore)
	{
		content->mode = get_mode(data);
		get_perms(data, content);
		content->links = ft_itoa(data.st_nlink);
		content->owner = get_owner(ctx, data.st_uid);
		content->group = get_group(ctx, data.st_gid);
		content->size = ft_itoa(data.st_size);
		content->time = time_helper(data.st_mtime);
	}
	content->mtime = data.st_mtim;
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

static void	get_perms(t_stat data, t_lslst *content)
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

static char	*time_helper(time_t ftime)
{
	time_t	fcurrent;
	char	*tmp;
	char	*current;
	char	*result;

	fcurrent = time(NULL);
	current = ctime(&fcurrent);
	current = ft_substr(current, ft_strlen(current) - 5, 5);
	mverif(current);
	tmp = ctime(&ftime);
	mverif(tmp);
	if (!ft_strnstr(tmp, current, ft_strlen(tmp)))
		result = old_time(tmp);
	else
		result = normal_time(tmp);
	free(current);
	return (result);
}
