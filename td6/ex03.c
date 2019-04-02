#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int nbThread;
	int numThread;
	pthread_mutex_t mut;
	pthread_cond_t cond;
} arg_t;

void *ft_thread_gen(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	pthread_mutex_lock(&(ptrbar->mut));
	ptrarg->nbIn = rand()%100 + 1;
	pthread_mutex_unlock(&(ptrbar->mut));
	printf("GENERATION FAITE\n");
	return NULL;
}

void *ft_thread_transmit(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	return ptrarg->;
}

void *ft_thread_end(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	printf("MASSAGE: %d");
}


int main(int argc, char **argv)
{
	if(argc > 1)
	{
		int i;
		arg_t arg;
		nbThreads = atoi(argv[1]);
		pthread_t id[nbThreads];
		pthread_mutex_t mut[nbThreads];
		pthread_cond_t cond[nbThreads];
		arg.nbFinish = 0;
		pthread_mutex_init(&arg.mut, NULL);
		pthread_cond_init(&arg.cond, NULL);
		
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
