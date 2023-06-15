#ifndef SAISIR_NOM_H
#define SAISIR_NOM_H

#include <stddef.h>
#include <stdio.h>

/**
 * Lis un nom d'une taille maximale spécifiée dans un fichier.
 * 
 * @param f FILE*, le fichier à lire
 * @param nom pointeur sur une chaine de caractères, stockera le nom saisi par l'utilisateur.
 * @param taille_nom size_t*, représente la taille actuelle de la chaîne 'nom'.
 * @param taille_max size_t, taille maximale du nom qui peut être lu dans le fichier.
 * 
 * @return int, renvoie 0 si la fonction s'est déroulée normalement, 1 si une erreur s'est produit.
 * Dans le cas d'une erreur, errno sera initialisé avec une valeur indiquant l'erreur.
 */
int saisirNom(FILE *f, char **nom, size_t *taille_nom, const size_t taille_max);

#endif
