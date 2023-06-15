#define _DEFAULT_SOURCE /* lstat */
#include "saisir_fichier.h"
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

/**
 * Vérifie si un chemin donné est un répertoire ou non.
 * 
 * @param chemin chaine de caractères, représente un chemin vers un fichier ou
 * un repertoire.
 * 
 * @return int, renvoie 1 si le chemin est un repertoire, 0 sinon. Renvoie -1 si une erreur
 * se produit.
 */
static int estRepertoire(const char *chemin) {
    struct stat fichier_stat;
    if (lstat(chemin, &fichier_stat) < 0) {
        return -1;
    }
    return S_ISDIR(fichier_stat.st_mode);
}

/**
 * Vérifie si un chemin vers un fichier possède une extension spécifique.
 * 
 * @param chemin chaine de caractères, représente un chemin vers un fichier
 * @param extension chaine de caractères, représente l'extension du chemin à vérifier.
 * 
 * @return int, renvoie 1 si le nom du fichier possède l'extension, 0 sinon.
 */
static int verifExtension(const char *chemin, const char *extension) {
    int taille_chemin = strlen(chemin);
    int taille_extension = strlen(extension);
    return taille_chemin > taille_extension && !strcmp(chemin + taille_chemin - taille_extension, extension);
}

int ouvreFichier(FILE **f, const char *chemin, const char *extension, const char *mode) {
    if (f == NULL || chemin == NULL || mode == NULL) {
        errno = EINVAL;
        return 1;
    }
    if (estRepertoire(chemin)) {
        errno = EISDIR;
        return 1;
    }
    if (extension && !verifExtension(chemin, extension)) {
        errno = ENOENT;
        return 1;
    }
    *f = fopen(chemin, mode);
    return *f == NULL ? 1 : 0;
}

