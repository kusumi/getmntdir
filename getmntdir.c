#if defined(__linux__)
/* Linux */
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <mntent.h>

char *getmntdir(const char *path)
{
	struct mntent *mnt;
	FILE *fp;
	char *f;
	static char s[PATH_MAX];

	s[sizeof(s) - 1] = '\0';
	strncpy(s, path, sizeof(s) - 1);

	while (strlen(s) > 1 && s[strlen(s)-1] == '/')
		s[strlen(s)-1] = '\0';

	f = realpath(s, NULL);
	if (!f)
		return NULL;

	if (!strcmp(f, "/")) {
		strcpy(s, "/");
		return s;
	}

	fp = setmntent("/proc/mounts", "r");
	if (!fp)
		return NULL;

	strcpy(s, "/");
	while ((mnt = getmntent(fp)) != NULL) {
		const char *mnt_dir = mnt->mnt_dir;
		int i = 0;

		if (!strcmp(f, mnt_dir)) {
			strncpy(s, mnt_dir, sizeof(s) - 1);
			break;
		}
		while (i < strlen(f)) {
			if (mnt_dir[i] == '\0' && strlen(mnt_dir) > strlen(s)) {
				strncpy(s, mnt_dir, sizeof(s) - 1);
				break;
			} else if (f[i] == mnt_dir[i]) {
				i++;
			} else
				break;
		}
	}
	endmntent(fp);

	return s;
}
#elif defined(__FreeBSD__) || defined(__DragonFly__) || defined(__OpenBSD__)
/* FreeBSD */
#include <sys/param.h>
#include <sys/mount.h>
#include <string.h>

char *getmntdir(const char *path)
{
	struct statfs st;
	static char s[PATH_MAX];

	if (statfs(path, &st))
		return NULL;

	strncpy(s, st.f_mntonname, sizeof(s) - 1);

	return s;
}
#elif defined(__NetBSD__)
/* NetBSD */
#include <sys/param.h>
#include <sys/statvfs.h>
#include <string.h>

char *getmntdir(const char *path)
{
	struct statvfs st;
	static char s[PATH_MAX];

	if (statvfs(path, &st))
		return NULL;

	strncpy(s, st.f_mntonname, sizeof(s) - 1);

	return s;
}
#else
#error "Not supported"
#endif
