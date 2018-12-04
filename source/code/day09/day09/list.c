#include <stdio.h>
#include <dirent.h>
#include <errno.h>
int main (int argc, char* argv[]) {
	if (argc < 2) {
		printf ("用法：%s <目录>\n", argv[0]);
		return -1;
	}
	DIR* dp = opendir (argv[1]);
	if (! dp) {
		perror ("opendir");
		return -1;
	}
	seekdir (dp, 1037918691);
	rewinddir (dp);
	long offset = telldir (dp);
	if (offset == -1) {
		perror ("telldir");
		return -1;
	}
	errno = 0;
	struct dirent* de;
	for (de = readdir (dp); de;
		de = readdir (dp)) {
		/*
		printf ("[%10ld %10ld] ", offset,
			de->d_off);
		*/
		printf ("[%10ld] ", offset);
		switch (de->d_type) {
			case DT_DIR:
				printf ("        目录：");
				break;
			case DT_REG:
				printf ("    普通文件：");
				break;
			case DT_LNK:
				printf ("      软链接：");
				break;
			case DT_BLK:
				printf ("      块设备：");
				break;
			case DT_CHR:
				printf ("    字符设备：");
				break;
			case DT_SOCK:
				printf ("Unix域套接字：");
				break;
			case DT_FIFO:
				printf ("    有名管道：");
				break;
			default:
				printf ("        未知：");
				break;
		}
		printf ("%s (%lu)\n", de->d_name,
			de->d_ino);
		if ((offset = telldir (dp)) == -1) {
			perror ("telldir");
			return -1;
		}
	}
	if (errno) {
		perror ("readdir");
		return -1;
	}
	closedir (dp);
	return 0;
}
