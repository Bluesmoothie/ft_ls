#include <stdio.h>

#include "ft_ls.h"

void	print_block(const t_param param, const t_block block) {
	// TODO use t_align data
	for (unsigned int i = 0; block.elem[i]; i++) {
		if (!param.long_format)
			printf("%s ", block.elem[i]->name);
		else
			printf("%c%s %lu %s %s %lu %d %d %d:%d %s\n", block.elem[i]->type, block.elem[i]->rights, block.elem[i]->links, block.elem[i]->owner, block.elem[i]->group, block.elem[i]->size, block.elem[i]->mtime.month, block.elem[i]->mtime.day, block.elem[i]->mtime.hour, block.elem[i]->mtime.minute, block.elem[i]->name);
	}
}