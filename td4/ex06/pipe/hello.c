#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	char buffer[16];
	int liaison[2];
	pipe(liaison);
	
	fflush(stdout); //clear stdout buffer !
	
	pid_t fils = fork();
	
	if(fils < 0){perror("Fork error !\n");}
	else if(fils == 0)
	{
		char msg[] = "Hello Papa !";
		close(liaison[0]);
		write(liaison[1], msg, sizeof(msg));
		close(liaison[1]);
	}
	else
	{
		close(liaison[1]);
		read(liaison[0], buffer, 16);
		close(liaison[0]);
		printf("Message du fils: %s\n", buffer);
		wait(NULL);
	}
	
	return 0;
}
