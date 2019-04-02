#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
	int nbThreads;
	int nbFinish;
	pthread_cond_t cond;
	pthread_mutex_t mut;
} barriere_t;

void *ft_thread(void *arg)
{
	printf("LANCE!\n");
	barriere_t *ptrbar = (barriere_t*)arg;
	int r = rand()%10 + 1;
	sleep(r); //Dirty Job !
	pthread_mutex_lock(&(ptrbar->mut));
	
	ptrbar->nbFinish++;
	if(ptrbar->nbFinish < ptrbar->nbThreads)
		pthread_cond_wait(&(ptrbar->cond), &(ptrbar->mut));
	else
		pthread_cond_broadcast(&(ptrbar->cond));
	
	pthread_mutex_unlock(&(ptrbar->mut));
	printf("TERMINE : %d\n", r);
	return NULL;
}

int main()
{
	int i;
	barriere_t bar;
	bar.nbThreads = 3;
	pthread_t id[bar.nbThreads];
	bar.nbFinish = 0;
	pthread_mutex_init(&bar.mut, NULL);
	pthread_cond_init(&bar.cond, NULL);
	
	srand(getpid());
	for(i=0; i<bar.nbThreads; i++)
		pthread_create(id+i, NULL, ft_thread, &bar);

	for(i=0; i<bar.nbThreads; i++)
		pthread_join(id[i], NULL);
	return 0;
}
