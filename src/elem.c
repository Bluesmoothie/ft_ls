#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <langinfo.h>

#include "ft_ls.h"

static void		decode_rights(const __mode_t mode, char rights[10]);
static char*	decode_owner(const __uid_t uid);
static char*	decode_group(const __gid_t gid);

__blkcnt_t	enrich_elem(const t_param param, t_elem* elem, const struct stat* statbuf) {
	const struct tm*	tm = localtime(&statbuf->st_mtime);

	if (param.long_format) {
		elem->type = decode_type(statbuf->st_mode);
		decode_rights(statbuf->st_mode, elem->rights);
		elem->links = statbuf->st_nlink;

		elem->uid = statbuf->st_uid;
		elem->owner = decode_owner(elem->uid);

		elem->gid = statbuf->st_gid;
		elem->group = decode_group(elem->gid);

		if (elem->type == 'b' || elem->type == 'c') {
			elem->size = major(statbuf->st_rdev);
			elem->size2 = minor(statbuf->st_rdev);
		}
		else
			elem->size = statbuf->st_size;

		elem->mtime.day = tm->tm_mday;
		elem->mtime.month = tm->tm_mon;
		elem->mtime.year = tm->tm_year + 1900;
		elem->mtime.hour = tm->tm_hour;
		elem->mtime.minute = tm->tm_min;

		elem->mtime.month_str = strdup(nl_langinfo(ABMON_1 + elem->mtime.month));
		if (!elem->mtime.month_str)
			exit(EXIT_FAILURE);

		elem->mtime.second = statbuf->st_mtim.tv_sec;
		elem->mtime.nanosecond = statbuf->st_mtim.tv_nsec;

	} else if (param.time_sort) {
		elem->mtime.second = statbuf->st_mtim.tv_sec;
		elem->mtime.nanosecond = statbuf->st_mtim.tv_nsec;
	}

	return statbuf->st_blocks;
}

char	decode_type(const __mode_t mode) {
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

static void	decode_rights(const __mode_t mode, char rights[10]) {
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

static char*	decode_owner(const __uid_t uid) {
	const struct passwd*	passwd = getpwuid(uid);

	return strdup(passwd->pw_name);
}	

static char*	decode_group(const __gid_t gid) {
	const struct group*	group = getgrgid(gid);

	return strdup(group->gr_name);
}