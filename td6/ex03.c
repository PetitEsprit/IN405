#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int numThread;
	int *in;
	int *out;
	pthread_mutex_t *mutin;
	pthread_mutex_t *mutout;
	pthread_cond_t *condin;
	pthread_cond_t *condout;
} arg_t;

void *ft_thread_first(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	pthread_mutex_lock(ptrarg->mutout);
	
	*(ptrarg->out) = rand()%100 + 1;
	printf("GENERATION FAITE: %d\n", *(ptrarg->out));
	pthread_cond_signal(ptrarg->condout);
	pthread_mutex_unlock(ptrarg->mutout);
	
	return NULL;
}

void *ft_thread_mid(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	pthread_mutex_lock(ptrarg->mutin);
	pthread_cond_wait(ptrarg->condin, ptrarg->mutin);
	int tmp = *(ptrarg->in);
	pthread_mutex_unlock(ptrarg->mutin);
	
	pthread_mutex_lock(ptrarg->mutout);
	*(ptrarg->out) = tmp;
	pthread_cond_signal(ptrarg->condout);
	pthread_mutex_unlock(ptrarg->mutout);
	printf("TRANSMITION FAITE\n");
	return NULL;
}

void *ft_thread_end(void *arg)
{
	arg_t *ptrarg = (arg_t*)arg;
	pthread_mutex_lock(ptrarg->mutin);
	pthread_cond_wait(ptrarg->condin, ptrarg->mutin);
	printf("FIN - MESSAGE: %d\n", *(ptrarg->in));
	pthread_mutex_unlock(ptrarg->mutin);
	return NULL;
}


int main(int argc, char **argv)
{
	if(argc > 1)
	{
		int i;
		int nbThreads = atoi(argv[1]);
		arg_t *arg = malloc(sizeof(arg_t)*nbThreads);
		pthread_t id[nbThreads];
		pthread_mutex_t mut[nbThreads];
		pthread_cond_t cond[nbThreads];
		int values[nbThreads];
		
		/*Init con et mut*/
		for(i=0;i<nbThreads;i++)
		{
			pthread_mutex_init(mut+i, NULL);
			pthread_cond_init(cond+i, NULL);
		}
		
		/*Init tab args*/
		arg[0].numThread = 0;
		arg[0].out = values+1;
		arg[0].mutout = mut;
		arg[0].condout = cond;
		for(i=1;i<nbThreads-1;i++)
		{
			arg[i].numThread = i;
			arg[i].in = values+i;
			arg[i].out = values+(i+1);
			arg[i].mutin = mut+(i-1);
			arg[i].mutout = mut+i;
			arg[i].condin = cond+(i-1);
			arg[i].condout = cond+i;
		}
		arg[i].numThread = i;
		arg[i].in = values+i;
		arg[i].mutin = mut+(i-1);
		arg[i].condin = cond+(i-1);
		/*Fin init args*/
		
		srand(getpid());
		
		/*Create*/
		for(i=1; i<nbThreads-1; i++)
			pthread_create(id+i, NULL, ft_thread_mid, &arg[i]);
		pthread_create(id+nbThreads-1, NULL, ft_thread_end, &arg[nbThreads-1]);
		sleep(1);
		pthread_create(id, NULL, ft_thread_first, &arg[0]);
		/*Join*/
		for(i=0; i<nbThreads; i++)
			pthread_join(id[i], NULL);
		free(arg);
		return 0;
	}
}
