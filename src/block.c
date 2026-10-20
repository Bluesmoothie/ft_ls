#define _GNU_SOURCE

#include <string.h>
#include <stdlib.h>

#include "ft_ls.h"

static int		compare(const void* a, const void* b, void* param);
static t_align	align_block(t_elem** elem);

t_block	enrich_block(const t_param param, t_block block, const bool readed_by_readdir) {
	for (unsigned int i = 0; block.elem[i]; i++) {
		const struct stat*	statbuf = check_arg(param, block.elem[i]->name, readed_by_readdir);
		if (!statbuf)
			continue;
		enrich_elem(param, (block.elem[i]), statbuf);
	}

	block.align = align_block(block.elem);

	return block;
}

void	recurse_block(const t_param param, const t_block block) {
	for (unsigned int i = 0; block.elem[i]; i++) {
		if (block.elem[i]->type == 'd' && strncmp(block.elem[i]->name, ".", 1))
			do_ls(param, block.elem[i]->name, true);
	}
}

void	sort_block(const t_param param, t_block block) {
	qsort_r(block.elem, block.nelem, sizeof(t_elem*), compare, (void*)&param);
}

static int	compare(const void* a, const void* b, void* param) {
	const short	c = ((const t_param*)param)->reverse_order ? -1 : 1;
	if (((const t_param*)param)->time_sort) {
		if ((*(const t_elem**)a)->mtime.second == (*(const t_elem**)b)->mtime.second) {
			if ((*(const t_elem**)a)->mtime.nanosecond == (*(const t_elem**)b)->mtime.nanosecond)
				return strcoll((*(const t_elem**)a)->name, (*(const t_elem**)b)->name) * c;
			else
			 	return ((*(const t_elem**)a)->mtime.nanosecond > (*(const t_elem**)b)->mtime.nanosecond) ? -c : c;
		} else {
			return ((*(const t_elem**)a)->mtime.second > (*(const t_elem**)b)->mtime.second) ? -c : c;
		}
	}
	return strcoll((*(const t_elem**)a)->name, (*(const t_elem**)b)->name) * c;
}

//	TODO
static t_align	align_block(t_elem** elem) {
	(void) elem; return (t_align){ 0 };
}