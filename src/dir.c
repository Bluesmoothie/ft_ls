#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "ft_ls.h"
#include "list.h"

t_elem**	enum_dir(const char* dir, size_t* nelem, const bool readed_by_readdir) {
	DIR*	dir_p = opendir(dir);
	if (!dir_p) {
		if (readed_by_readdir) {
			if (!g_error_code)
				g_error_code = 1;
		} else
			g_error_code = 2;
		print_err(ERR_ACC, dir);
		dprintf(STDERR_FILENO, "%s\n", strerror(errno));
		return NULL;
	}
	
	t_list*	dir_lst = NULL;
	struct dirent*	dirent = readdir(dir_p);

	while (dirent) {
		t_elem*	elem = calloc(1, sizeof(t_elem));
		t_list*	node = list_new_node(elem);
		if (!elem || !node)
			exit(EXIT_FAILURE);

		elem->name = strdup(dirent->d_name);
		if (!elem->name)
			exit(EXIT_FAILURE);
		if (elem->name[0] == '/') {		//	if name start with '/' the this is already a full path
			elem->path = strdup(elem->name);
			if (!elem->path)
				exit(EXIT_FAILURE);
		} else {
			elem->path = malloc(strlen(elem->name) + strlen(dir) + 2);	//	+2 for \0 and dir/name
			if (!elem->path)
				exit(EXIT_FAILURE);
			elem->path = strcpy(elem->path, dir);
			if (elem->path[0] && elem->path[strlen(elem->path) - 1] != '/')
				elem->path = strcat(elem->path, "/");
			elem->path = strcat(elem->path, elem->name);
		}
		if (dirent->d_type == DT_DIR)	//	permit recursivity to work without long format option
			elem->type = 'd';
		list_push_back(&dir_lst, node);
		dirent = readdir(dir_p);
	}
	closedir(dir_p);

	t_elem**	array = list_to_array(dir_lst, nelem);
	if (!array)
		exit(EXIT_FAILURE);
	list_clear_no_free_elem(dir_lst);
	return array;
}