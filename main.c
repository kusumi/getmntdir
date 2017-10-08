#include <stdio.h>
#include <stdlib.h>

#include "./getmntdir.h"

int main(int argc, char **argv)
{
	int i;

	if (argc == 1) {
		fprintf(stderr, "Usage: %s [path1] [path2]...\n", argv[0]);
		exit(1);
	}

	for (i = 1; i < argc; i++) {
		const char *path, *dir;

		path = argv[i];
		dir = getmntdir(path);

		printf("%s -> %s\n", path, dir);
	}

	return 0;
}
