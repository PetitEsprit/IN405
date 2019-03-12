#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n = 0;
	pid_t pid = 1;
	pid_t childpid;
	
	while(pid > 0 && n < 10){pid = fork();n++;}
	
	if(pid == 0)
	{
		srand((unsigned) getpid());
		sleep(rand()%10 + 1);
		printf("Je suis le FILS %d\n", getpid());
		exit(0);
	}
	else
	{
		while(n != 0)
		{
			childpid = wait(NULL);
			printf("LE FILS %d TERMINE\n", childpid);
			n--;
		}
	}
	
	return 0;
}