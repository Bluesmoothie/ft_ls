/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:51 by ygille            #+#    #+#             */
/*   Updated: 2025/04/16 14:34:14 by ygille           ###   ########.fr       */
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
# include <pwd.h>
# include <grp.h>

# include "libft.h"
# include "ft_printf.h"

# include "t_lslst.h"
# include "t_lslst2.h"

# define MINOR_ERROR	1
# define MAJOR_ERROR	2

# define DIRTYPE_DIR	4

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

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
}	t_context;

enum	e_erros
{
	ELS_ACCESS,
	ELS_OPEN
};

//	main.c
void		process_request(t_context ctx);

//	align.c
void		align_data(t_lslst2 *content);

//	clean.c
t_lslst2	*remove_ucontent(t_lslst2 *content, t_param param);

//	data.c
int			get_more_data(t_lslst2 *content, char *path, bool moremore);

//	data2.c
char		*get_owner(int uid);
char		*get_group(int gid);
char		*normal_time(char *src);
char		*old_time(char *src);

//	debug.c
void		print_context(t_context ctx);
void		print_lslst(t_lslst *lst);

//	error.c
void		pexit(void);
void		ft_perror(int error, char *arg);
void		*mverif(void *ptr);

//	ft_ls.c
void		ls_path(t_context ctx, char *arg);

//	parse.c
t_context	parse_args(int argc, char **argv);

//	print.c
void		print_content(t_lslst2 *content, t_param param, int size);

//	recursive.c
void		add_subfolder(t_context ctx, char *name);

//	sort.c
t_lslst2	*time_sort(t_lslst2 *content, t_param param);
t_lslst2	*alpha_sort(t_lslst2 *content, t_param param);

//	resolve.c
char		*resolve_path(char *arg, char **envp);

//	utils.c
t_dirent	*readdir_helper(DIR *dir);
int			ft_strcmp_casei(const char *s1, const char *s2);

//	verifs.c
void		verif_paths(t_lslst *lst);

#endif