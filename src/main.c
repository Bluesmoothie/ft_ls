#include <unistd.h>
#include <stdlib.h>
#include <locale.h>

#include "ft_ls.h"

int g_error_code = 0;

int	main(int argc, char** argv) {
	
	t_param	param = { 0 };
	int		opt;

	while ((opt = getopt(argc, argv, "lRart")) != -1) {
		switch(opt) {

			case 'l':
				param.long_format = true;
				break;

			case 'R':
				param.recursive = true;
				param.multiple_entries = true;
				break;

			case 'a':
				param.show_hidden = true;
				break;

			case 'r':
				param.reverse_order = true;
				break;

			case 't':
				param.time_sort = true;
				break;

			case '?':
				print_help();
				exit(EXIT_FAILURE);
				break;

			default:
				break;
		}
	}

	if (argc - optind > 1)	param.multiple_entries = true;

	setlocale(LC_ALL, "");

	// Using . as default if nothing is given
	if (optind == argc)
		do_ls(param, ".", false);
	else
		treat_args_and_do_ls(param, optind, argc, argv);

	return g_error_code;
}