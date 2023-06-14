#ifndef SAISIR_NOM_H
#define SAISIR_NOM_H

#include <stddef.h>
#include <stdio.h>

#define TAILLE_MAX_NOM 20

int saisirNom(FILE *f, char **nom, size_t *taille_nom);

#endif
