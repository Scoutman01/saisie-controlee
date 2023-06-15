#include "contenu_fichier.h"
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long contenuFichier(char **contenu, size_t *n, FILE *f, int ligne) {
    int carac;
    long nb_carac = 0;
    const int t_init = 16;

    if (contenu == NULL || n == NULL || f == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (*contenu == NULL || *n == 0) {
        *contenu = (char*) malloc(t_init);
        if (*contenu == NULL) {
            errno = ENOMEM;
            return -1;
        }
        *n = t_init;
    }
    
    /* Si le fichier est l'entrée standard, que ligne est égale à zéro
    et que la saisie se fait au clavier, alors le programme sera en attente
    jusqu'à ce que la fin du fichier soit saisie manuellement (CTRL+d). */
    while ((carac = fgetc(f)) != EOF) {
        nb_carac++;
        if (nb_carac >= *n) {
            size_t t_realloc = (*n * 2) + 1; /* +1 pour le caractère nul */
            char *tmp = (char *) realloc(*contenu, t_realloc);
            if (tmp == NULL) {
                errno = ENOMEM;
                return -1;
            }
            *contenu = tmp;
            *n = t_realloc;
            /* dépassement de capacité */
            if (LONG_MAX < *n) {
                errno = ERANGE;
                return -1;
            }
        }
        (*contenu)[nb_carac - 1] = carac;
        if (carac == '\n' && ligne) {
            break;
        }
    }

    if (carac == EOF && nb_carac == 0) {
        errno = EIO;
        return -1;
    }
    
    (*contenu)[nb_carac] = '\0';
    return nb_carac;
}