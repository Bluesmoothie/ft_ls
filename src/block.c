#include "ft_ls.h"

static t_align	align_block(t_elem** elem);

t_block	enrich_block(const t_param param, t_block block, const bool readed_by_readdir) {
	for (unsigned int i = 0; block.elem[i]; i++) {
		const struct stat*	statbuf = check_arg(param, block.elem[i]->name, readed_by_readdir);
		char*	name = block.elem[i]->name;
		*(block.elem[i]) = enrich_elem(statbuf);
		block.elem[i]->name = name;
	}

	block.align = align_block(block.elem);

	return block;
}

void	recurse_block(const t_param param, const t_block block) {
	for (unsigned int i = 0; block.elem[i]; i++) {
		if (block.elem[i]->type == 'd')
			do_ls(param, block.elem[i]->name, true);
	}
}

//	TODO
static t_align	align_block(t_elem** elem) {
	(void) elem; return (t_align){ 0 };
}