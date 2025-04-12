/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:37:47 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 00:17:28 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	verif(void *ptr);

void	pexit(void)
{
	perror(NULL);
	exit (-1);
}

void	ft_perror(int error, char *arg)
{
	char *str1;
	char *str2;

	str1 = NULL;
	str2 = NULL;
	if (error == ELS_ACCESS)
	{
		str1 = ft_strjoin("ls: can't access '", arg);
		verif(str1);
		str2 = ft_strjoin(str1, "'");
		verif(str2);
	}
	else if (error == ELS_OPEN)
	{
		str1 = ft_strjoin("ls: can't open directory '", arg);
		verif(str1);
		str2 = ft_strjoin(str1, "'");
		verif(str2);
	}
	perror(str2);
	free(str1);
	free(str2);
}

static void	verif(void *ptr)
{
	if (!ptr)
		exit(-1);
}
