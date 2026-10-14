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

extern int	g_error_code;

//	ls.c
void	do_ls(const t_param param, char* arg);

//	msg.c
void	print_help(void);