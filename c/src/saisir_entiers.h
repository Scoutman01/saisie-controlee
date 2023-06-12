#ifndef __SAISIE_ENTIERS__
#define __SAISIE_ENTIERS__

#include <stddef.h>
#include <stdio.h>

/**
 * @brief Représente le choix à faire lorsque que la saisie d'un entier n'est pas correcte.
 * 
 * QUITTER : quitter complètement la saisie
 * RECOMMENCER : recommencer depuis le début la saisie
 * REPRENDRE : reprendre la saisie à partir du dernier entier valide
 * 
 */
typedef enum {
    QUITTER,
    RECOMMENCER,
    REPRENDRE
} Option;

/**
 * @brief Lis des entiers à partir d'un fichier et les stocke dans un tableau,
 * avec des options pour gérer les cas de fin de fichier ou d'entrées non valides.
 * 
 * @param f pointeur sur une structure FILE, à partir duquel les entiers doivent être lus.
 * @param entiers pointeur sur un tableau d'entiers, où les valeurs d'entrée seront stockées.
 * @param nb_attendus le nombre d'entiers à lire dans le fichier.
 * @param opt Option, représente l'option à utiliser lors de la saisie des entiers.
 * 
 * @return size_t, le nombre d'entiers lus, ou -1 si une erreur se produit.
 */
size_t saisirEntiers(FILE *f, int *entiers, const size_t nb_attendus, Option opt);

#endif
