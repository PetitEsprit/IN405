#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int n = 0;
	//fflush(stdout); //clear stdout buffer !
	
	pid_t fils = fork();
	
	if(fils < 0){perror("Fork error !\n");}
	else if(fils == 0)
	{
		srand((unsigned) getpid());
		n = rand()%50 + 1;
		printf("FILS: %d\n", n);
		exit(n);
	}
	else
	{
		wait(&n);
		//utiliser macro WIFEXITED pour vérifier fin de process normal 
		printf("PERE: %d\n", WEXITSTATUS(n)); //macro pour décoder renvoie
	}
	
	return 0;
}
