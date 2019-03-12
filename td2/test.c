#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "se_fichier.h"



int main (int argc, char ** argv) {
	
	int i;
	SE_FICHIER f = SE_ouverture ("test", O_RDWR);
	//SE_ecritureEntier (f, 9);
	
	SE_lectureEntier (f, &i);
	printf("R: %d\n", i);
	SE_fermeture(f);

	return 0;
}
