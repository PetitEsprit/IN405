#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Enumération des différents opérateurs possibles
typedef enum {
	OCD_SOMME,
	OCD_MOYENNE,
	OCD_MAX,
	OCD_MIN,
	OCD_TOTAL
} opcode_t;

// Structure contenant les arguments du programme
typedef struct {
	int nbThreads;			//< Nombre de threads à utiliser
	int tailleTableau;		//< Taille du tableau utilisé pour la réduction
	opcode_t code;			//< Opération à réaliser
} arg_t;

// Structure contenant les informations nécessaires au thread
typedef struct {
	int *tab;				//< Tableau d'entiers à traiter
	int start;				//< Indice de début de traitement
	int end;				//< Indice de fin de traitement (non compris)
	int *res;				//< Résultat local
	pthread_mutex_t *ptrmut;
} message_t;

// Alias de pointeurs de fonction
typedef int (* ptrVerif) (int *, int, int);

// Fonction thread -- calcule la somme locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * sommeTableau (void * arg)
{
	message_t *m = (message_t*)arg;
	for(int i=m->start; i<m->end; i++)
	{
		pthread_mutex_lock(m->ptrmut);
		*(m->res) += m->tab[i];
		printf("res: %d\n", *(m->res));
		pthread_mutex_unlock(m->ptrmut);
	}
	return NULL;
}


// Fonction thread -- calcule la moyenne locale d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * moyenneTableau (void * arg)
{  
	return NULL;
}


// Fonction thread -- calcule le maximum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * maxTableau (void * arg)
{
	return NULL;
}

// Fonction thread -- calcule le minimum local d'un tableau
// \param	arg 			Message transmis par le thread père
// \return					NULL
void * minTableau (void * arg)
{
	return NULL;
}

// NE PAS TOUCHER
// Fonction de vérification -- somme des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifSomme (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- moyenne des éléments du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMoyenne (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	if (tailleTableau == 0)
		return resultat == 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp += tableau [i];

	return resultat == (tmp / tailleTableau);
}

// NE PAS TOUCHER
// Fonction de vérification -- maximum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMax (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 0;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp < tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// NE PAS TOUCHER
// Fonction de vérification -- minimum du tableau
// \param	tableau			Tableau d'entiers
// \param	tailleTableau	Taille du tableau d'entiers
// \param	resultat		Résultat obtenu par la réduction
// \return					VRAI si le résultat est juste, FAUX sinon
int verifMin (int * tableau, int tailleTableau, int resultat) {
	int i, tmp = 101;

	for (i = 0; i < tailleTableau; ++i)
		tmp = (tmp > tableau [i] ? tableau [i] : tmp);

	return resultat == tmp;
}

// Analyse des arguments du programme. Quitte si le nombre d'arguments est
// différent de 4. Remplit la structure de données des arguments.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Structure de données des arguments
arg_t analyseArguments (int argc, char ** argv)
{
	arg_t a = {0, 0, 0};
	if(argc == 4)
	{
		a.nbThreads = atoi(argv[1]);
		a.tailleTableau = atoi(argv[2]);
		switch(argv[3][0])
		{
			case '+':
				a.code = OCD_SOMME;
			break;
			case '/':
				a.code = OCD_MOYENNE;
			break;
			case 'M':
				a.code = OCD_MAX;
			break;
			case 'm':
				a.code = OCD_MIN;
			break;
			default:
				printf("Opcode non reconnue !\n");
			break;
		}
	}
	return a;
}

// NE PAS TOUCHER
// Récupération de la fonction de vérification à partir de l'opcode
// \param	opcode 			Code de l'opération
// \return					Pointeur de la fonction de vérification
ptrVerif decodeOpcodeVerif (const opcode_t o) {
	switch (o) {
		case OCD_SOMME:		return verifSomme;
		case OCD_MOYENNE:	return verifMoyenne;
		case OCD_MAX:		return verifMax;
		case OCD_MIN:		return verifMin;
		default:
			printf ("L'opération n'a pas été reconnue\n");
			exit (-1);
	}
}

// Génération du tableau avec des entiers compris entre 1 et 100.
// \param	tailleTableau	Taille du tableau d'entiers
// \return					Tableau d'entiers
int * genereTableau (int tailleTableau)
{  
	int *t = (int*)malloc(sizeof(int) * tailleTableau);
	for(int i=0; i<tailleTableau; i++)
		t[i] = rand()%100 + 1;
	return t;
}

void debugPrintTab(int *t, int taille)
{
	
	for(int i=0; i<taille; i++)
	{
		printf("%d ", t[i]);
	}
	printf("\n");
}

void debugPrintTabMsg(message_t *m, int taille)
{
	for(int i=0; i<taille; i++)
	{
		printf("MSG No%d:\n", i);
		printf("\tstart: %d\n", m[i].start);
		printf("\tend: %d\n", m[i].end);
		printf("\tres: %d\n", m[i].res);
	}
}

// Fonction chargée de la réduction multi-threadé, elle va initialiser les
// différentes variables utilisées par les threads (tableau d'entier, messages,
// etc.) puis créer les threads. Une fois l'exécution des threads terminée et
// la réduction opérée, la vérification du résultat est faite.
// \param	arg 			Arguments du programme décodés
void programmePrincipal (const arg_t arg) {
	// Déclaration des variables
	int * tab= NULL;
	int decal,res = 0;
	pthread_t id[arg.nbThreads];
	message_t *m;
	pthread_mutex_t mutex;
	void *(*operation) (void *); int (*reduc) (message_t *, int);

	// Allocation de la mémoire
	tab = genereTableau(arg.tailleTableau);
	// Initialisation des variables et création des threads
	
	decal = arg.tailleTableau / arg.nbThreads;
	m = (message_t*)malloc(sizeof(message_t) * arg.nbThreads);
	pthread_mutex_init(&mutex,NULL);
	for(int i=0; i<arg.nbThreads; i++)
	{
		m[i].tab = tab;
		m[i].start = decal*i;
		m[i].end = decal*(i+1);
		m[i].res = &res;
		m[i].ptrmut = &mutex;
	}
	
	
	if(m[arg.nbThreads-1].end != arg.tailleTableau)
		m[arg.nbThreads-1].end = arg.tailleTableau;
		
	switch(arg.code)
	{
		case OCD_SOMME: 
			operation = sommeTableau;
		break;
		case OCD_MOYENNE:
			operation = moyenneTableau;
		break;
		case OCD_MAX:
			operation = maxTableau;
		break;
		case OCD_MIN:
			operation = minTableau;
		break;
	}
	
	for(int i=0; i<arg.nbThreads; i++)
	{
		pthread_create(id+i, NULL, operation, m+i);
	}
	// Jointure
	for(int i=0; i<arg.nbThreads; i++)
	{
		pthread_join(id[i], NULL);
	}
	
	// NE PAS TOUCHER
	if ( (* (decodeOpcodeVerif (arg.code) ) ) (tab, arg.tailleTableau, res) )
		printf ("Le resultat est juste.\n");
	else printf ("Le resultat est faux.\n");
	// FIN
	
	debugPrintTab(tab, arg.tailleTableau);
	debugPrintTabMsg(m, arg.nbThreads);
	printf("res: %d\n", res);
	// Libération de la mémoire
	free(tab);
}

// NE PAS TOUCHER
// Fonction main -- analyse les arguments donnés au
// programme, puis exécute le programme principal, chargé de la réduction
// multi-threadée.
// \param	argc			Nombre d'arguments
// \param	argv			Arguments
// \return					Code de retour du programme (0 en cas de réussite)
int main (int argc, char ** argv) {
	arg_t a;

	srand (time (NULL) );

	a = analyseArguments (argc, argv);
	programmePrincipal (a);
	
	return 0;
}
