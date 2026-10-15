#include <stdio.h>
#include <unistd.h>

#include "msg.h"

void	print_help(void) {
	fprintf(stderr, MSG_HELP);
}

void	print_err(const int err_id, const char* arg) {
	dprintf(STDERR_FILENO, error_message[err_id], arg);
}