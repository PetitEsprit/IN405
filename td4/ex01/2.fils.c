#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t pid = fork();
	
	printf("Mon PID est %d", (int)getpid());
	if(pid == 0) //this is the child process ...
		printf(" et celui de mon pere est %d\n", (int)getppid());
	else
	{
		printf(" et celui de mon fils est %d\n", (int)pid);
		wait(NULL);
	}
	
	return 0;
}
