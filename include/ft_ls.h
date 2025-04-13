/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/13 19:55:30 by ygille           ###   ########.fr       */
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
# include "t_lslst2.h"

# define MINOR_ERROR	1
# define MAJOR_ERROR	2	

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

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

enum	e_erros
{
	ELS_ACCESS,
	ELS_OPEN
};

//	main.c
void		process_request(t_context ctx);

//	data.c
t_lslst2	*get_more_data(t_lslst2 *content);

//	debug.c
void		print_context(t_context ctx);
void		print_lslst(t_lslst *lst);

//	error.c
void		pexit(void);
void		ft_perror(int error, char *arg);
void		mverif(void *ptr);

//	ft_getcwd.c
char		*ft_getcwd(char **envp);

//	ft_ls.c
void		ls_path(t_context ctx, char *arg);

//	parse.c
t_context	parse_args(int argc, char **argv, char **envp);

//	print.c
void		print_content(t_lslst2 *content, t_param param);

//	time.c
t_lslst2	*get_file_time(t_lslst2 *content);

//	resolve.c
char		*resolve_path(char *arg, char **envp);

//	utils.c
t_dirent	*readdir_helper(DIR *dir);
int			ft_strcmp_casei(const char *s1, const char *s2);

//	verifs.c
void		verif_paths(t_lslst *lst);

#endif