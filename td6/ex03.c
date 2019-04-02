#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *ft_thread_gen(void *arg)
{
	int r = rand()%100 + 1;
	printf("GENERATION FAITE : %d\n", r);
	return r;
}

void *ft_thread_transmit(void *arg)
{
	int n = (int)arg;
	return n;
}

void *ft_thread_end(void *arg)
{
	int n = (int)arg;
	printf("MESSAGE : %d\n", n); 
}


int main(int argc, char **argv)
{
	if(argc > 1)
	{
		int i;
		
		srand(getpid());
		pthread_create(id, NULL, ft_thread, &arg);
		pthread_join(id[0], NULL);
		
		for(i=1; i<bar.nbThreads-1; i++)
		{
			pthread_create(id+i, NULL, ft_thread, &arg);
			pthread_join(id[i], NULL);
		}
		
		pthread_create(id+nbThreads-1, NULL, ft_thread, &arg);
		pthread_join(id[nbThreads-1], NULL);
		return 0;
	}
}
