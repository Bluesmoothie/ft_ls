#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"
#include "list.h"

t_elem**	enum_dir(const char* dir, size_t* nelem) {
	DIR*	dir_p = opendir(dir);
	if (!dir_p)
		exit(EXIT_FAILURE);
	
	t_list*	dir_lst = NULL;
	struct dirent*	dirent = readdir(dir_p);

	while (dirent) {
		t_elem*	elem = malloc(sizeof(t_elem));
		t_list*	node = list_new_node(elem);
		if (!elem || !node)
			exit(EXIT_FAILURE);

		elem->name = strdup(dirent->d_name);
		if (!elem->name)
			exit(EXIT_FAILURE);
		elem->path = malloc(strlen(elem->name) + strlen(dir) + 2);	//	+2 for \0 and dir/name
		if (!elem->path)
			exit(EXIT_FAILURE);
		elem->path = strcpy(elem->path, dir);
		elem->path = strcat(elem->path, "/");
		elem->path = strcat(elem->path, elem->name);
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