#include <stdio.h>

#include "ft_ls.h"

void	print_file(const t_param param, const t_elem elem) {
	if (!param.long_format)
		printf("%s ", elem.name);
	else
		printf("%c%s %lu %s %s %lu %d %d %d:%d %s", elem.type, elem.rights, elem.links, elem.owner, elem.group, elem.size, elem.mtime.month, elem.mtime.day, elem.mtime.hour, elem.mtime.minute, elem.name);
}