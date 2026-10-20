#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "ft_ls.h"
#include "list.h"

t_elem**	enum_dir(const char* dir) {
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

		elem->name = dirent->d_name;
		if (dirent->d_type == DT_DIR)	//	permit recursivity to work without long format option
			elem->type = 'd';
		list_push_back(&dir_lst, node);
		dirent = readdir(dir_p);
	}

	t_elem**	array = list_to_array(dir_lst);
	if (!array)
		exit(EXIT_FAILURE);
	list_clear_no_free_elem(dir_lst);
	return array;
}