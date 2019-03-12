#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	pid_t pid = fork();
	
	if(pid == 0)
	{
		for(i=1; i<=5;i++)
		{
			fflush(stdout);
			printf("FILS: SECONDE %d !", i);
			sleep(1);
		}
	}
	else
	{
		sleep(3);
		kill(pid,SIGSTOP);
		sleep(5);
		kill(pid,SIGCONT);
	}
	return 0;
}
