#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

void fileInfo(char *filename)
{
	struct stat st;
	lstat(filename, &st);
	struct passwd* user = getpwuid(st.st_uid);
	
	if(S_ISREG(st.st_mode)) printf("Regular File");
	if(S_ISDIR(st.st_mode)) printf("Directory ");
	if(S_ISBLK(st.st_mode)) printf("Block Device");
	if(S_ISFIFO(st.st_mode)) printf("FIFO");
	if(S_ISLNK(st.st_mode)) printf("Symbolic Link");
	if(S_ISSOCK(st.st_mode)) printf("Socket");
	printf(" ");
	((st.st_mode & S_IRUSR) != 0) ? printf("r") : printf("-");
	((st.st_mode & S_IWUSR) != 0) ? printf("w") : printf("-");
	((st.st_mode & S_IXUSR) != 0) ? printf("x") : printf("-");
	((st.st_mode & S_IRGRP) != 0) ? printf("r") : printf("-");
	((st.st_mode & S_IWGRP) != 0) ? printf("w") : printf("-");
	((st.st_mode & S_IXGRP) != 0) ? printf("x") : printf("-");
	((st.st_mode & S_IROTH) != 0) ? printf("r") : printf("-");
	((st.st_mode & S_IWOTH) != 0) ? printf("w") : printf("-");
	((st.st_mode & S_IXOTH) != 0) ? printf("x") : printf("-");
	printf(" %s %d ", user->pw_name, st.st_size);
	printf("%s\n", filename);
}

int main()
{
	fileInfo("test");
	
	return 0;
}
