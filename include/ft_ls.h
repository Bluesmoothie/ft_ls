#pragma once

#include <stdbool.h>
#include <sys/stat.h>

typedef struct	s_param {
	bool	long_format;
	bool	recursive;
	bool	show_hidden;
	bool	reverse_order;
	bool	time_sort;
	bool	multiple_entries;
}	t_param;

typedef struct	s_time {
	int	day;
	int	month;
	int	year;
	int	hour;
	int	minute;
}	t_time;

typedef struct	s_elem {
	char*		name;
	char		type;
	char		rights[10];
	__nlink_t	links;
	__uid_t		uid;
	char*		owner;
	__gid_t		gid;
	char*		group;
	__off_t		size;
	__off_t		size2;	// for b or c type file
	t_time		mtime;
}	t_elem;

typedef enum	e_error_code {
	ERR_ARG
}	t_error_code;

extern int	g_error_code;

//	ls.c
void	do_ls(const t_param param, char* arg, const bool readed_by_readdir);
void	order_args_and_do_ls(const t_param param, int optind, const int argc, char** argv);

// elem.c
t_elem	enrich_elem(const struct stat* statbuf);
char	decode_type(const __mode_t mode);

//	msg.c
void	print_help(void);
void	print_err(const int err_id, const char* arg);

//	print.c
void	print_file(const t_param param, const struct stat* statbuf, const t_elem elem);