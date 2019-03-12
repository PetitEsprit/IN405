#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int pid = fork();
	printf("Hello World\n");
	if(pid > 0) wait(NULL);
	return 0;
}
