#include <bits/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "ft_ls.h"

void	print_block(const t_param param, const t_block block) {
	// TODO use t_align data
	struct timespec	now;
	clock_gettime(CLOCK_REALTIME, &now);
	const __time_t	six_month_ago = now.tv_sec - 15778476;

	if (block.elem[0] && block.print_total_and_name)
		printf("%s:\ntotal %lu\n", block.name, block.total);

	for (unsigned int i = 0; block.elem[i]; i++) {
		if (!param.show_hidden && !strncmp(block.elem[i]->name, ".", 1))
			continue;
		if (!param.long_format)
			printf("%s  ", block.elem[i]->name);
		else if (six_month_ago < block.elem[i]->mtime.second && block.elem[i]->mtime.second < now.tv_sec)
			printf("%c%s %lu %s %s %lu %d %d %d:%d %s\n", block.elem[i]->type, block.elem[i]->rights, block.elem[i]->links, block.elem[i]->owner, block.elem[i]->group, block.elem[i]->size, block.elem[i]->mtime.month, block.elem[i]->mtime.day, block.elem[i]->mtime.hour, block.elem[i]->mtime.minute, block.elem[i]->name);
		else 
			printf("%c%s %lu %s %s %lu %d %d %d  %s\n", block.elem[i]->type, block.elem[i]->rights, block.elem[i]->links, block.elem[i]->owner, block.elem[i]->group, block.elem[i]->size, block.elem[i]->mtime.month, block.elem[i]->mtime.day, block.elem[i]->mtime.year, block.elem[i]->name);
	}
	printf("\n");
}