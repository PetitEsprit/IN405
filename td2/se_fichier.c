#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "se_fichier.h"


// Ouverture du fichier
// \param	chemin			Nom/chemin du fichier à ouvrir
// \param	acces			Accès au fichier (cf. flags de open() )
// \return					Structure FICHIER (le descripteur est mis à -1
//							si l'ouverture a échouée)
SE_FICHIER SE_ouverture (const char * chemin, int acces)
{
	SE_FICHIER f;
	f.descripteur = open(chemin, acces | O_CREAT , 0600);
	f.chemin = (char*)malloc(sizeof(char)*(strlen(chemin)+1));
	strcpy(f.chemin, chemin);
 	f.acces = acces;
	
	return f;
}

// Fermeture du fichier
// \param	fichier			Structure FICHIER à fermer
// \return					-1 si échec, 0 sinon
int SE_fermeture (SE_FICHIER fichier)
{
	free(fichier.chemin);
	fichier.acces = 0;
	return close(fichier.descripteur);
}

// Suppresion de fichier
// \param	chemin			Nom/chemin du fichier à supprimer
// \return					-1 si échec, 0 sinon
int SE_suppression (const char * chemin)
{
	return unlink(chemin);
}

// Lecture d'un caractère à partir d'un fichier
// \param	fichier			Structure FICHIER où lire
// \param	caractere		Pointeur du caractère lu
// \return					-1 si échec, 0 si fin du fichier,
//							nombres d'octets lus sinon
int SE_lectureCaractere (SE_FICHIER fichier, char * caractere)
{
	return read(fichier.descripteur, caractere, sizeof(char));
}

// Ecriture d'un caractère dans un fichier
// \param	fichier			Structure FICHIER où écrire
// \param	caractere		Caractère à écrire
// \return					-1 si échec, nombre d'octets écrits sinon
int SE_ecritureCaractere (SE_FICHIER fichier ,const char caractere)
{
	return write(fichier.descripteur, &caractere, sizeof(char));
}


// Lecture d'une chaîne de caractère dans un fichier
// \param	fichier			Structure FICHIER où lire
// \param	chaine			Chaîne lue
// \param	taille			Taille max de la chaîne lue
// \return					-1 si échec, 0 si fin du fichier,
//							nombre d'octets lus sinon
int SE_lectureChaine (SE_FICHIER fichier, char * chaine, int tailleMax)
{
	int i,n;
	
	if(fichier.descripteur == -1) return -1;
	i  = n = SE_lectureCaractere(fichier, chaine);
	while(i < tailleMax && n > 0)
	{
		n = SE_lectureCaractere(fichier, chaine+i);
		i++;
	}
	return i;
}

// Ecriture d'une chaîne de caractère dans un fichier
// \param	fichier			Structure FICHIER où écrire
// \param	chaine			Chaîne de caractère à écrire
// \param	taille			Taille de la chaîne à écrire
// \return					-1 si échec, nombre d'octets écrits sinon
int SE_ecritureChaine (SE_FICHIER fichier, const char * chaine, int taille)
{
	int i;
	int n;
	
	if(fichier.descripteur == -1) return -1;
	i  = n = SE_ecritureCaractere(fichier, chaine[0]);
	while(i < taille && n > 0)
	{
		n = SE_ecritureCaractere(fichier, chaine[i]);
		i++;
	}
	return i;
}

// Lecture d'un entier dans un fichier
// \param	fichier			Structure FICHIER où lire
// \param	entier			Entier lu
// \return					-1 si échec, 0 si fin du fichier,
//							nombre d'octets lus sinon
int SE_lectureEntier (SE_FICHIER fichier, int * entier)
{
	char c;
	int  nb = 0;
	int nbdigit = 0;
	
	while(SE_lectureCaractere(fichier, &c) && !(c >= '0' && c <= '9'));
	if(c >= '0' && c <= '9'){nbdigit++; nb=nb*10+(int)(c - '0');}
	while(SE_lectureCaractere(fichier, &c) && (c >= '0' && c <= '9'))
	{
		nbdigit++;
		nb=nb*10+(int)(c - '0');
	}
	*entier = nb;
	return nbdigit;
}

// Ecriture d'un entier dans un fichier
// \param	fichier			Structure FICHIER où écrire
// \param	entier			Entier à écrire
// \return					-1 si échec, nombre d'octets écrits sinon
int SE_ecritureEntier (SE_FICHIER fichier, const int entier)
{
	int n = entier;
	int static cpt = 0;
	
	if(n/10 == 0)
	{
		return SE_ecritureCaractere (fichier ,(char)(n%10+'0'));
	}
	else
	{
		cpt++;
		SE_ecritureEntier (fichier, n/10);
		SE_ecritureCaractere (fichier ,(char)(n%10+'0'));
	}
	return cpt;
}
