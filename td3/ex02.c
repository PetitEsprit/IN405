#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR* d; struct dirent* rdir;
	d = opendir(".");
	while((rdir = readdir(d)) != NULL)
		printf("%s\n", rdir->d_name);
	closedir(d);
	return 0;
}
