#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int fgen(int m, int ninit)
{
	if(m ==0) return 0;
	
	int i;
	int n = ninit;
	int nbfils = 0;
	int nbpetitfils = 0;
	
	pid_t pid = 1;
	while(pid > 0 && 0 < n) //pere crée m fils
	{	
		pid = fork();
		if(pid==0)printf("WAAH;");
		n--;
		nbfils++;//plus de fils!
	}
	if(pid==0 && m > 0) //si fils crée d'autre fils(il est le pere de ses fils)
	{
		fgen(m-1,ninit);
	}

	i = 0;
	while(i<nbfils)
	{
		wait(&nbpetitfils);
		nbfils += WEXITSTATUS(nbpetitfils);
		i++;
	}
	return nbfils;
}

int main()
{
	const int minit = 2;
	const int ninit = 3;
	fgen(minit, ninit);
	return 0;
}
