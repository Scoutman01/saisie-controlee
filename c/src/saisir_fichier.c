#define _DEFAULT_SOURCE /* lstat */
#include "saisir_fichier.h"
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

static int estRepertoire(const char *chemin) {
    struct stat fichier_stat;
    if (lstat(chemin, &fichier_stat) < 0) {
        return -1;
    }
    return S_ISDIR(fichier_stat.st_mode);
}

static int verifExtension(const char *chemin, const char *extension) {
    char taille_chemin, taille_extension;
    taille_chemin = strlen(chemin);
    taille_extension = strlen(extension);
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

