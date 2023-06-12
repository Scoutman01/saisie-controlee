#ifndef __CONTENU_FICHIER__
#define __CONTENU_FICHIER__

#include <stdio.h>

/**
 * @brief Lis le contenu d'un fichier et alloue dynamiquement de la mémoire pour stocker le contenu si nécessaire.
 * 
 * @param contenu pointeur vers un pointeur sur un caractère, qui contiendra le contenu du fichier lu
 * @param n pointeur sur une variable size_t, qui représente la taille du tampon alloué à la ligne d'entrée.
 * Il est utilisé pour garder une trace de la taille actuelle du tampon et pour le réallouer dynamiquement si nécessaire.
 * @param f pointeur sur une structure FILE, qui représente le fichier à lire.
 * @param ligne entier qui indique si la fonction doit arrêter la lecture du fichier après avoir rencontré un retour à la ligne.
 * @return long, le nombre de caractères lus dans le fichier, ou -1 si une erreur se produit, dans le cas d'une erreur, errno
 * sera initialisé avec une valeur indiquant l'erreur et le tableau contenu doit être libéré par la fonction appelante.
 */
long contenuFichier(char **contenu, size_t *n, FILE *f, int ligne);

#endif
