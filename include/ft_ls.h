/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/12 23:33:22 by ygille           ###   ########.fr       */
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

# include "t_lslst.h"

# define MINOR_ERROR	1
# define MAJOR_ERROR	2	

typedef struct stat		t_stat;
typedef struct dirent 	t_dirent;

typedef struct s_param
{
	bool	hidden;
	bool	longformat;
	bool	recursive;
	bool	reverse;
	bool	timesort;
}	t_param;

typedef struct s_context
{
	t_param	param;
	t_lslst	*lst;
	int		code;
	bool	multiple;
	bool	cwd_mode;
	char	*cwd;
}	t_context;

//	main.c
void		process_request(t_context ctx);

//	debug.c
void		print_context(t_context ctx);

//	error.c
void		pexit(void);

//	ft_getcwd.c
char		*ft_getcwd(char **envp);

//	ft_ls.c
void		ls_path(t_context ctx, char *path, char *arg);

//	parse.c
t_context	parse_args(int argc, char **argv, char **envp);

//	print.c
void		print_content(t_list *content);

//	resolve.c
char		*resolve_path(char *arg, char **envp);

//	utils.c
t_dirent	*readdir_helper(DIR *dir);
int			ft_strcmp_casei(const char *s1, const char *s2);

//	verifs.c
void		verif_paths(t_lslst *lst);

#endif