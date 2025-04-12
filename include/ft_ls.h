/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 20:55:57 by ygille           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

# include "libft.h"
# include "ft_printf.h"

typedef struct stat		t_stat;
typedef struct dirent 	t_dirent;

typedef struct s_param
{
	bool	hidden;
}	t_param;

//	main.c

//	error.c
void	pexit(void);

//	ft_getcwd.c
char	*ft_getcwd(char **envp);

//	ft_ls.c
bool	ls_path(char *path, char *arg, bool mul, t_param para);

//	print.c
void	print_content(t_list *content);

//	resolve.c
char	*resolve_path(char *arg, char **envp);

//	utils.c
t_dirent	*readdir_helper(DIR *dir);
int			ft_strcmp_casei(const char *s1, const char *s2);

//	verifs.c
bool	verif_path(char *path, char *arg);

#endif