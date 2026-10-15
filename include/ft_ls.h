#pragma once

#include <stdbool.h>

typedef struct	s_param {
	bool	long_format;
	bool	recursive;
	bool	show_hidden;
	bool	reverse_order;
	bool	time_sort;
	bool	multiple_entries;
}	t_param;

typedef struct	s_elem {
	char*			name;
	char			type;
	char			rights[10];
	unsigned int	hardlinks;
	char*			owner;
	char*			group;
	unsigned int	size;
	char*			mtime;
}	t_elem;

typedef enum	e_error_code {
	ERR_ARG
}	t_error_code;

extern int	g_error_code;

//	ls.c
void	do_ls(const t_param param, char* arg, const bool readed_by_readdir);

// elem.c
t_elem	enrich_elem(const struct stat* statbuf);

//	msg.c
void	print_help(void);
void	print_err(const int err_id, const char* arg);