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
	
	i = 0; nbfils = 0; nbpfils = 0;
	while(i<ninit)
	{
		if((pid = fork()) == 0)
		{
			printf("WAAH\n");
			fgen(m-1, ninit);
			exit(ninit);
		}
			i++;
	}

	nbpfils = 0;nbfils = ninit;
	
	for(i=0;i<ninit;i++)
	{
		wait(&nbpfils);
		nbfils += WEXITSTATUS(nbpfils); 
	}
	return nbfils;
}

int main()
{
	const int minit = 2;
	const int ninit = 2;
	int i = fgen(minit, ninit);
	printf("i : %d\n", i);
	return 0;
}
