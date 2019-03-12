#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int fgen(int m, int ninit)
{
	if(m == 0) return 0;
	int i,nbfils, nbpfils;
	pid_t pid;
	fflush(stdout); //flush the f-ing memory
	for(i=0;i<ninit;i++)
	{
		if((pid = fork())==0)
		{
			printf("WAAH\n");
			fgen(m-1, ninit);
			exit(0);
		}
	}

	nbpfils = nbfils = 0;
	
	for(i=0;i<ninit;i++)
	{
		
		wait();
	}
	return nbfils;
}

int main()
{
	const int minit = 2;
	const int ninit = 1;
	int i = fgen(minit, ninit);
	printf("i : %d\n", i);
	return 0;
}
