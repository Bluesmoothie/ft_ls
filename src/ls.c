#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "ft_ls.h"

static struct stat*	check_arg(const t_param param, const char* arg, const bool readed_by_readdir);

void	do_ls(const t_param param, char* arg, const bool readed_by_readdir) {
	const struct stat*	statbuf = check_arg(param, arg, readed_by_readdir);
	t_elem				elem = { 0 };
	if (!statbuf) {
		if (!readed_by_readdir)
			print_err(ERR_ARG, arg);
		return;
	}

	elem.name = arg;
	if (param.long_format)
		elem = enrich_elem(statbuf);

	if (!S_ISDIR(statbuf->st_mode))
		print_file(param, statbuf, elem);
}

static struct stat*	check_arg(const t_param param, const char* arg, const bool readed_by_readdir) {
	int				ret = 0;
	struct stat*	statbuf = malloc(sizeof(struct stat));
	if (!statbuf)
		exit(EXIT_FAILURE);

	if (readed_by_readdir || param.long_format) {
		if (lstat(arg, statbuf)) {
			free(statbuf);
			if (readed_by_readdir)
				if (!g_error_code)
					g_error_code = 1;
			else
				g_error_code = 2;
			return NULL;
		}
		return statbuf;
	}

	ret = stat(arg, statbuf);
	if (!ret && S_ISDIR(statbuf->st_mode))
		return statbuf;
	
	if (!ret || (ret && errno == ENOENT)) {
		free(statbuf);
		ret = lstat(arg, statbuf);
	}

	if (ret) {
		free(statbuf);
		g_error_code = 2;
		return NULL;
	}

	return statbuf;
}