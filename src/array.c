#include <stdlib.h>

#include "ft_ls.h"
#include "list.h"

t_elem**	list_to_array(t_list* list, size_t* size) {
	const unsigned int	c = list_count(list);
	if (c < 1)
		return NULL;
	t_elem**	array = malloc((c + 1) * sizeof(t_elem*));
	if (!array)
		return NULL;

	unsigned int	n = 0;
	do {
		array[n++] = list->elem;
		list = list->next;
	}	while (list);
	array[n] = NULL;

	if (size)
		*size = c;
	return array;
}

void	free_array(t_elem** array, const bool free_name) {
	if (!array)
		return;

	unsigned int	n = 0;
	while (array[n]) {
		if (free_name)
			free(array[n]->name);
		free(array[n]->path);
		if (array[n]->owner)
			free(array[n]->owner);
		if (array[n]->group)
			free(array[n]->group);
		if (array[n]->mtime.month_str)
			free(array[n]->mtime.month_str);
		free(array[n++]);
	}
	free(array);
}