#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	const int minit = 3;
	const int ninit = 3;
	int m,n;
	
	int i = 0;
	pid_t pid = 1;
	int nbproctotal = 0;
	int nbfils = 0;
	int nbpetitfils = 0;
	
	m = minit;
	while(pid > 0 && 0 < m) //pere crée fils...
	{	
		pid = fork();
		nbfils++;
		m--;
	}
	
	n = ninit;
	if(pid == 0)//si fils ....
	{
		pid = 1;
		while(pid > 0 && 0 < n)//crée petit fils
		{
			pid = fork();
			nbpetitfils++;
			n--;
		}
		exit(nbpetitfils);//renvoie nb petit fils
	}
	else
	{
		m = minit;
		while(m > 0)// pour tous les fils crées attend nb petits fils
		{
			wait(&i);
			nbproctotal += WEXITSTATUS(i); // ajoute nb petit fils
			m--;
		}
		nbproctotal += nbfils; //ajoute nbfils;
		printf("nbproc:%d\n", nbproctotal);
	}
	return 0;
}
