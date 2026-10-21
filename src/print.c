#include <bits/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "ft_ls.h"

void	print_block(const t_param param, const t_block block) {
	// TODO use t_align data
	static bool		started = false;
	bool			visible = false;
	struct timespec	now;
	clock_gettime(CLOCK_REALTIME, &now);
	const __time_t	six_month_ago = now.tv_sec - 15778476;

	if (block.elem[0] && block.name && (param.multiple_entries || param.recursive)) {
		if (started)
			printf("\n");
		printf("%s:\n", block.name);
		started = true;
	}
	if (block.elem[0] && param.long_format) {
		printf("total %lu\n", block.total);
		started = true;
	}

	for (unsigned int i = 0; block.elem[i]; i++) {
		if (!param.show_hidden && !strncmp(block.elem[i]->name, ".", 1))
			continue;
		visible = true;
		if (!param.long_format)
			printf("%s  ", block.elem[i]->name);
		else {
			printf("%c%s %*lu %-*s %-*s ",
				block.elem[i]->type,
				block.elem[i]->rights,
				block.align.link, block.elem[i]->links,
				block.align.owner, block.elem[i]->owner,
				block.align.group, block.elem[i]->group);
			if (block.elem[i]->type == 'b' || block.elem[i]->type == 'c') {
				int	pad = block.align.size - (block.align.size2 + 2 + block.align.size3);
				printf("%*lu, %*lu ",
					block.align.size2 + (pad > 0 ? pad : 0), block.elem[i]->size,
					block.align.size3, block.elem[i]->size2);
			}
			else
				printf("%*lu ", block.align.size, block.elem[i]->size);
			printf("%-*s %2d ",
				block.align.month, block.elem[i]->mtime.month_str,
				block.elem[i]->mtime.day);

			if ((six_month_ago < block.elem[i]->mtime.second
				|| (six_month_ago == block.elem[i]->mtime.second && now.tv_nsec < block.elem[i]->mtime.nanosecond))
				&& (block.elem[i]->mtime.second < now.tv_sec
				|| (block.elem[i]->mtime.second == now.tv_sec && block.elem[i]->mtime.nanosecond < now.tv_nsec)))
				printf("%02d:%02d %s\n",
					block.elem[i]->mtime.hour,
					block.elem[i]->mtime.minute,
					block.elem[i]->name);
			else 
				printf(" %d %s\n", 
					block.elem[i]->mtime.year, 
					block.elem[i]->name);
			}
	}
	if (!param.long_format && visible) {
		printf("\n");
		started = true;
	}
}