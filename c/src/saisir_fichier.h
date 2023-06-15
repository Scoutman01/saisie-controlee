#ifndef SAISIR_FICHIER_H
#define SAISIR_FICHIER_H

#include <stdio.h>

/**
 * Ouvre un fichier dont le chemin d'accès, l'extension et le mode d'ouverture sont spécifiés
 * et renvoie un code d'erreur si le fichier ne peut être ouvert.
 * 
 * @param f FILE**, utilisée pour stocker le pointeur de fichier après l'avoir ouvert.
 * @param chemin chaine de caractères, Chemin d'accès au fichier à ouvrir.
 * @param extension chaine de caractères, représente l'extension du fichier que la
 * fonction doit vérifier lors de l'ouverture du fichier (peut-être mis à NULL).
 * @param mode chaine de caractères, spécifie le mode d'ouverture du fichier.
 * 
 * @return int, renvoie 0 si le fichier a été ouvert avec succès et 1 s'il y a eu une erreur.
 * Dans le cas d'une erreur, errno sera initialisé avec une valeur indiquant l'erreur.
 */
int ouvreFichier(FILE **f, const char *chemin, const char *extension, const char *mode);

#endif
