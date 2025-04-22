/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cache.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:27:06 by ygille            #+#    #+#             */
/*   Updated: 2025/04/22 14:29:23 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	search_id(t_cache *cache, int id);

void	init_cache(t_context *ctx)
{
	if (ctx->param.show_user)
	{
		ctx->users_cache = malloc(sizeof(t_cache));
		if (!ctx->users_cache)
			exit(-1);
		for (int i = 0;i < CACHE_SIZE;i++)
		{
			ctx->users_cache->id[i] = EMPTY_ID;
		}
	}
	if (ctx->param.show_group)
	{
		ctx->groups_cache = malloc(sizeof(t_cache));
		if (!ctx->groups_cache)
			exit(-1);
		for (int i = 0;i < CACHE_SIZE;i++)
		{
			ctx->groups_cache->id[i] = EMPTY_ID;
		}
	}
}

char	*get_owner(t_context ctx, int uid)
{
	t_passwd	*data;
	const int	i = search_id(ctx.users_cache, uid);
	
	if (ctx.users_cache->id[i] == EMPTY_ID)
	{
		data = getpwuid(uid);
		ctx.users_cache->id[i] = uid;
		ctx.users_cache->str[i] = mverif(ft_strdup(data->pw_name));
	}
	return (ctx.users_cache->str[i]);
}

char	*get_group(t_context ctx, int gid)
{
	t_group	*data;
	const int	i = search_id(ctx.groups_cache, gid);
	
	if (ctx.groups_cache->id[i] == EMPTY_ID)
	{
		data = getgrgid(gid);
		ctx.groups_cache->id[i] = gid;
		ctx.groups_cache->str[i] = mverif(ft_strdup(data->gr_name));
	}
	return (ctx.groups_cache->str[i]);
}

void	free_cache(t_context ctx)
{
	if (ctx.param.show_user)
	{
		for (int i = 0;ctx.users_cache->id[i] != EMPTY_ID;i++)
			free(ctx.users_cache->str[i]);
		free(ctx.users_cache);
	}
	if (ctx.param.show_group)
	{
		for (int i = 0;ctx.groups_cache->id[i] != EMPTY_ID;i++)
			free(ctx.groups_cache->str[i]);
		free(ctx.groups_cache);
	}
}

static int	search_id(t_cache *cache, int id)
{
	int			i;

	i = 0;
	while (i < CACHE_SIZE && cache->id[i] != id && cache->id[i] != EMPTY_ID)
		i++;
	if (i == CACHE_SIZE)
		exit (-1);
	return (i);
}
