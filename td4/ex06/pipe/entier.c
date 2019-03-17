#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int buffer[2] = {0};
	int liaison[2];
	pipe(liaison);
	
	fflush(stdout); //clear stdout buffer !
	
	pid_t fils = fork();
	
	if(fils < 0){perror("Fork error !\n");}
	else if(fils == 0)
	{
		int n[2] = {10,50};
		close(liaison[0]);
		write(liaison[1], n, sizeof(int));
		write(liaison[1], n+1, sizeof(int));
		close(liaison[1]);
	}
	else
	{
		close(liaison[1]);
		read(liaison[0], buffer, sizeof(int));
		read(liaison[0], buffer+1, sizeof(int));
		close(liaison[0]);
		printf("Message du fils: %d %d\n", buffer[0] , buffer[1]);
		wait(NULL);
	}
	
	return 0;
}
