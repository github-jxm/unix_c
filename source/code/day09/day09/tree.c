#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
/* 以树的形式显示一个目录的内容 */
int tree (char const* dir, size_t depth) {
	DIR* dp = opendir (dir);
	if (! dp) {
		perror ("opendir");
		return -1;
	}
	if (chdir (dir) == -1) {
		perror ("chdir");
		return -1;
	}
	errno = 0;
	struct dirent* de;
	for (de = readdir (dp); de;
		de = readdir (dp))
		if (de->d_type != DT_DIR)
			printf ("%*s%s\n", depth * 2, "",
				de->d_name);
		else if (strcmp (de->d_name, ".") &&
			strcmp (de->d_name, "..")) {
			printf ("%*s%s/\n", depth * 2, "",
				de->d_name);
			if (tree (de->d_name, depth + 1) == -1)
				return -1;
		}
	if (errno) {
		perror ("readdir");
		return -1;
	}
	if (chdir ("..") == -1) {
		perror ("chdir");
		return -1;
	}
	closedir (dp);
	return 0;
}
int main (int argc, char* argv[]) {
	if (argc < 2) {
		printf ("用法：%s <目录>\n", argv[0]);
		return -1;
	}
	printf ("%s/\n", argv[1]);
	return tree (argv[1], 1);
}
