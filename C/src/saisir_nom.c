#include "saisir_nom.h"
#include "contenu_fichier.h"
#include <ctype.h>
#include <errno.h>

/**
 * Vérifie si une chaîne de caractères donnée ne contient que des caractères alphanumériques.
 * 
 * @param nom chaine de caractères, représente un nom/pseudo.
 * 
 * @return int, renvoie 1 si la chaîne 'nom' contient un caractère non alphanumérique, 0 sinon.
 */
static int caracteresValide(const char *nom) {
    int i;
    for (i = 0; nom[i]; i++) {
        if (!isalnum(nom[i])) {
            return 1;
        }
    }
    return 0;
}

int saisirNom(FILE *f, char **nom, size_t *taille_nom, const size_t taille_max) {
    size_t t_nom;
    long nb_carac = -1;
    
    if (f == NULL || nom == NULL) {
        errno = EINVAL;
        return 1;
    }

    if (taille_nom == NULL) {
        t_nom = 0;
    } else {
        t_nom = *taille_nom;
    }
    
    while (nb_carac <= 0 || nb_carac > taille_max) {
        nb_carac = contenuFichier(nom, &t_nom, f, 1);
        if (nb_carac < 0) {
            return 1;
        }
        /* enlève le retour à la ligne */
        nb_carac--;
        (*nom)[nb_carac] = '\0';
        if (caracteresValide(*nom)) {
            nb_carac = -1;
        }
    }
    
    if (taille_nom) {
        *taille_nom = nb_carac;
    }
    return 0;
}