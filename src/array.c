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

void	free_array(t_elem** array) {
	if (!array)
		return;

	unsigned int	n = 0;
	while (array[n])
		free(array[n++]);
	free(array);
}