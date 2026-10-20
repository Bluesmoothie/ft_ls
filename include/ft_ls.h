#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "list.h"

typedef struct	s_param {
	bool	long_format;
	bool	recursive;
	bool	show_hidden;
	bool	reverse_order;
	bool	time_sort;
	bool	multiple_entries;
}	t_param;

typedef struct	s_time {
	int					day;
	int					month;
	int					year;
	int					hour;
	int					minute;
	__time_t 			second;			//	full seconds including hour,year,month,day (for time sort)
	__syscall_slong_t	nanosecond;
}	t_time;

typedef struct	s_elem {
	char*		name;
	char*		path;
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

typedef struct s_align {
	unsigned int	link;
	unsigned int	owner;
	unsigned int	group;
	unsigned int	size;
} t_align;

typedef struct s_block {
	char*		name;
	t_elem**	elem;
	size_t		nelem;
	__blkcnt_t	total;
	bool		print_total;
	t_align		align;
} t_block;

typedef enum	e_error_code {
	ERR_ARG
}	t_error_code;

extern int	g_error_code;

//	ls.c
void			do_ls(const t_param param, char* dir, const bool readed_by_readdir);
void			treat_args_and_do_ls(const t_param param, int optind, const int argc, char** argv);
struct stat*	check_arg(const t_param param, const char* arg, const bool readed_by_readdir);

//	array.c
t_elem**		list_to_array(t_list* list, size_t* size);
void			free_array(t_elem** array);

//	block.c
t_block			enrich_block(const t_param param, t_block block, const bool readed_by_readdir);
void			recurse_block(const t_param param, const t_block block);
void			sort_block(const t_param param, t_block block);

//	dir.c
t_elem**		enum_dir(const char* dir, size_t* nelem);

//	elem.c
void			enrich_elem(const t_param param, t_elem* elem, const struct stat* statbuf);
char			decode_type(const __mode_t mode);

//	msg.c
void			print_help(void);
void			print_err(const int err_id, const char* arg);

//	print.c
void			print_block(const t_param param, const t_block block);