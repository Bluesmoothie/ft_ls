#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "ft_ls.h"
#include "list.h"

void	do_ls(const t_param param, char* arg, const bool readed_by_readdir) {
	const struct stat*	statbuf = check_arg(param, arg, readed_by_readdir);
	t_elem				elem = { 0 };
	if (!statbuf) {
		if (!readed_by_readdir)
			print_err(ERR_ARG, arg);
		return;
	}

	if (param.long_format)
		elem = enrich_elem(statbuf);

	elem.name = arg;
}

void	treat_args_and_do_ls(const t_param param, int optind, const int argc, char** argv) {
	t_list*	file_lst = NULL;
	t_list*	folder_lst = NULL;

	while (optind < argc) {
		const struct stat*	statbuf = check_arg(param, argv[optind], false);
		if (!statbuf) {
			print_err(ERR_ARG, argv[optind]);
			continue;
		}

		t_elem*	elem = malloc(sizeof(t_elem));
		if (!elem)
			exit(EXIT_FAILURE);

		elem->name = argv[optind];
		elem->type = decode_type(statbuf->st_mode);

		t_list*	node = list_new_node(elem);
		if (!node)
			exit(EXIT_FAILURE);

		if (elem->type == 'd')
			list_push_back(&folder_lst, node);
		else
		 	list_push_back(&file_lst, node);

		optind++;
	}

	t_elem**	file_array = list_to_array(file_lst);
	// t_elem**	folder_array = list_to_array(folder_lst);	// TODO

	list_clear_no_free_elem(file_lst);
	list_clear_no_free_elem(folder_lst);

	if (file_array) {
		t_block	block = { 0 };
		block.elem = file_array;
		if (param.long_format)
			block = enrich_block(param, block, false);
		print_block(param, block);
	}

	// TODO
	// if (folder_array) {
	// 	for (int i = 0; folder_array[i]; i++)
	// 		do_ls(param, folder_array[i]->name, false);
	// 	fflush(stdout);
	// 	write(STDOUT_FILENO, "\n", 1);
	// 	free_array(folder_array);
	// }
}

struct stat*	check_arg(const t_param param, const char* arg, const bool readed_by_readdir) {
	int				ret = 0;
	struct stat*	statbuf = malloc(sizeof(struct stat));
	if (!statbuf)
		exit(EXIT_FAILURE);

	if (readed_by_readdir || param.long_format) {
		if (lstat(arg, statbuf)) {
			free(statbuf);
			if (readed_by_readdir) {
				if (!g_error_code)
					g_error_code = 1;
			}
			else
				g_error_code = 2;
			return NULL;
		}
		return statbuf;
	}

	ret = stat(arg, statbuf);
	if (!ret && S_ISDIR(statbuf->st_mode))
		return statbuf;
	
	if (!ret || (ret && errno == ENOENT))
		ret = lstat(arg, statbuf);

	if (ret) {
		free(statbuf);
		g_error_code = 2;
		return NULL;
	}

	return statbuf;
}