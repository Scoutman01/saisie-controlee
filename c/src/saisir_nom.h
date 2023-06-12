#ifndef __SAISIE_NOM__
#define __SAISIE_NOM__

#include <stddef.h>
#include <stdio.h>

#define TAILLE_MAX_NOM 20

int saisirNom(FILE *f, char **nom, size_t *taille_nom);

#endif
