/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygille <ygille@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:04:51 by ygille            #+#    #+#             */
/*   Updated: 2025/05/07 13:11:18 by ygille           ###   ########.fr       */
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

# define MINOR_ERROR	1
# define MAJOR_ERROR	2

# define DIRTYPE_DIR	4

# define CACHE_SIZE		1024
# define EMPTY_ID		-1

typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct s_cache
{
	int		id[CACHE_SIZE];
	char	*str[CACHE_SIZE];
}	t_cache;

enum	e_time_modes
{
	TM_MODIF = 0,
	TM_ACCESS,
	TM_CREATE
};

enum	e_spec_modes
{
	SM_FALSE,
	SM_TRUE,
	SM_BLOCKED
};

typedef struct s_param
{
	bool	hidden;
	bool	recursive;
	bool	sort;
	bool	show_user;
	bool	show_group;
	char	longformat;
	char	reverse;
	char	timesort;
	char	color;
	char	time_mode;
}	t_param;

typedef struct s_context
{
	t_param	param;
	t_list	*args;
	t_list	*files;
	t_list	*directories;
	t_cache	*users_cache;
	t_cache	*groups_cache;
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
void		align_data(t_lslst *content);

//	cache.c
void		init_cache(t_context *ctx);
char		*get_owner(t_context ctx, int uid);
char		*get_group(t_context ctx, int gid);
void		free_cache(t_context ctx);

//	clean.c
t_lslst		*remove_ucontent(t_lslst *content, t_param param);

//	data.c
int			get_more_data(t_context ctx, t_lslst *content, char *path, char moremore);

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
void		print_content(t_lslst *content, t_param param, int size);

//	recursive.c
void		add_subfolder(t_context ctx, char *name, char *upper);

//	sort.c
t_lslst		*time_sort(t_lslst *content, t_param param);
t_lslst		*alpha_sort(t_lslst *content, t_param param);

//	specials.c
void		special_options(char *option);

//	time.c
char		*normal_time(char *src);
char		*old_time(char *src);

//	resolve.c
char		*resolve_path(char *arg, char **envp);

//	utils.c
t_dirent	*readdir_helper(DIR *dir);
int			ft_strcmp_casei(const char *s1, const char *s2);
void		verif_paths(t_list *lst, t_list **files, t_list **directories);

# define HELP_MSG	"Usage: ls [OPTION]... [FILE]...\n\
List information about the FILEs (the current directory by default).\n\
Sort entries alphabetically if none of -cftuSUX is specified.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
  -a, --all                  do not ignore entries starting with .\n\
  -A, --almost-all           do not list implied . and ..\n\
      --author               with -l, print the author of each file\n\
  -c                         with -lt: sort by, and show, ctime (time of last\n\
                               modification of file status information);\n\
                               with -l: show ctime and sort by name;\n\
                               otherwise: sort by ctime, newest first\n\
      --color[=WHEN]         colorize the output; WHEN can be 'always' (default\n\
                               if omitted), 'auto', or 'never'; more info below\n\
  -d, --directory            list directories themselves, not their contents\n\
  -f                         do not sort, enable -aU, disable -ls --color\n\
  -g                         like -l, but do not list owner\n\
      --group-directories-first\n\
                             group directories before files;\n\
                               can be augmented with a --sort option, but any\n\
                               use of --sort=none (-U) disables grouping\n\
  -G, --no-group             in a long listing, don't print group names\n\
  -l                         use a long listing format\n\
  -m                         fill width with a comma separated list of entries\n\
  -n, --numeric-uid-gid      like -l, but list numeric user and group IDs\n\
  -o                         like -l, but do not list group information\n\
  -r, --reverse              reverse order while sorting\n\
  -R, --recursive            list subdirectories recursively\n\
  -S                         sort by file size, largest first\n\
  -t                         sort by time, newest first; see --time\n\
  -u                         with -lt: sort by, and show, access time;\n\
                               with -l: show access time and sort by name;\n\
                               otherwise: sort by access time, newest first\n\
  -U                         do not sort; list entries in directory order\n\
  -x                         list entries by lines instead of by columns\n\
  -X                         sort alphabetically by entry extension\n\
  -1                         list one file per line.  Avoid '\\n' with -q or -b\n\
      --help     display this help and exit\n\
      --version  output version information and exit\n\
	\n\
Using color to distinguish file types is disabled both by default and\n\
with --color=never.  With --color=auto, ls emits color codes only when\n\
standard output is connected to a terminal.  The LS_COLORS environment\n\
variable can change the settings.  Use the dircolors command to set it.\n\
	\n\
Exit status:\n\
 0  if OK,\n\
 1  if minor problems (e.g., cannot access subdirectory),\n\
 2  if serious trouble (e.g., cannot access command-line argument).\n"

# define VER_MSG	"ft_ls v1\n"

#endif