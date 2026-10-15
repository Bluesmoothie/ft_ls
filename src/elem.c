#include <sys/stat.h>

#include "ft_ls.h"

static char	decode_type(__mode_t mode);
static void	decode_rights(__mode_t mode, char rights[10]);

t_elem	enrich_elem(const struct stat* statbuf) {
	t_elem	elem = { 0 };
	elem.type = decode_type(statbuf->st_mode);
	decode_rights(statbuf->st_mode, elem.rights);
	return elem;
}

static char	decode_type(__mode_t mode) {
	if (S_ISREG(mode))
		return '-';
	if (S_ISDIR(mode))
		return 'd';
	if (S_ISLNK(mode))
		return 'l';
	if (S_ISCHR(mode))
		return 'c';
	if (S_ISBLK(mode))
		return 'b';
	if (S_ISFIFO(mode))
		return 'p';
	if (S_ISSOCK(mode))
		return 's';

	return '-';
}

static void	decode_rights(__mode_t mode, char rights[10]) {
	rights[0] = (mode & S_IRUSR) ? 'r' : '-';
	rights[1] = (mode & S_IWUSR) ? 'w' : '-';
	rights[2] = (mode & S_IXUSR) ? 'x' : '-';
	rights[3] = (mode & S_IRGRP) ? 'r' : '-';
	rights[4] = (mode & S_IWGRP) ? 'w' : '-';
	rights[5] = (mode & S_IXGRP) ? 'x' : '-';
	rights[6] = (mode & S_IROTH) ? 'r' : '-';
	rights[7] = (mode & S_IWOTH) ? 'w' : '-';
	rights[8] = (mode & S_IXOTH) ? 'x' : '-';

	if (mode & S_ISUID)
	    rights[2] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
	    rights[5] = (mode & S_IXGRP) ? 's' : 'S';
	if (mode & S_ISVTX)
	    rights[8] = (mode & S_IXOTH) ? 't' : 'T';

	rights[9] = '\0';
}