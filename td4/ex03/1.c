#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	const int minit = 3;
	const int ninit = 2;
	int m,n;
	
	int i = 0;
	pid_t pid = 1;
	int nbfils = 0;
	
	m = minit;
	while(0 < m)
	{
		n = ninit;
		while(pid > 0 && 0 < n)
		{
			pid = fork();
			nbfils++;
			n--;
		}
		m--;
	}
	if(pid == 0){printf("WAAH!");}
	if(pid > 0)
	{
		printf("Nb fils: %d\n", nbfils);
		wait(NULL);
	}
	return 0;
}
