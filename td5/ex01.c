#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void* hello(void *arg)
{
	printf("Hello World !\n");
	return NULL;
}

void* printalea1(void *arg)
{
	int n = *(int*)arg;
	printf("Alea1: %d\n", n);
	return NULL;
}

void* printalea2(void *arg)
{
	long int n = rand()%100;
	printf("Alea2 Thread: %ld\n", n);
	return (void*)n;
}

void* printalea3(void *arg)
{
	int s = 0;
	int *t = (int*)arg;
	for(int i=0; i<5;i++)
		s+=t[i];
	printf("Somme du tableau = %d\n", s);
	return NULL;
}

void* printalea4(void *arg)
{
	int s = 0;
	int *t = (int*)arg;
	int n = t[0];
	printf("n :%d\n", n);
	for(int i=1; i<n;i++)
		s+=t[i];
	printf("Somme du tableau2 = %d\n", s);
	return NULL;
}

int main(int argc, char **argv)
{
	srand(getpid());
	int alea1, alea2, alea3[5], alea[4], n;
	int *alea4;
	
	alea1 = rand()%100;
	n = atoi(argv[1]);
	alea4 = (int*)malloc(sizeof(int) * (n+1));
	for(int i=0;i<5;i++)
		alea3[i] = rand() % 100;
	
	alea4[0] = n;
	for(int i=0;i<n;i++)
		alea4[i+1] = rand() % 100;
	
	pthread_t id[5];
	pthread_create(id, NULL, hello, NULL);
	pthread_create(id+1, NULL, printalea1, &alea1);
	pthread_create(id+2, NULL, printalea2, NULL);
	pthread_create(id+3, NULL, printalea3, &alea3);
	pthread_create(id+4, NULL, printalea4, alea4);
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	pthread_join(id[2], (void**)&alea2);
	printf("Alea2 Main: %d\n", alea2);
	pthread_join(id[3], NULL);
	pthread_join(id[4], NULL);
	
	free(alea4);
	return 0;
}
