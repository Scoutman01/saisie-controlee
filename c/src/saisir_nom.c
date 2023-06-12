#include "saisir_nom.h"
#include "contenu_fichier.h"
#include <ctype.h>
#include <errno.h>

static int caracteresValide(const char *nom) {
    int i;
    for (i = 0; nom[i]; i++) {
        if (!isalnum(nom[i])) {
            return 1;
        }
    }
    return 0;
}

int saisirNom(char **nom, size_t *taille_nom) {
    size_t t_nom;
    long nb_carac = -1;
    
    if (nom == NULL) {
        errno = EINVAL;
        return 1;
    }

    if (taille_nom == NULL || *taille_nom <= 0) {
        t_nom = 0;
    } else {
        t_nom = *taille_nom;
    }
    
    /* -1 pour enlever le retour à la ligne */
    while (nb_carac - 1 <= 0 || nb_carac - 1 > TAILLE_MAX_NOM) {
        nb_carac = contenuFichier(nom, &t_nom, stdin, 1);
        if (nb_carac < 0) {
            return 1;
        }
        /* enlève le retour à la ligne */
        (*nom)[nb_carac - 1] = '\0';
        if (caracteresValide(*nom)) {
            nb_carac = -1;
        }
    }
    
    if (taille_nom) {
        *taille_nom = nb_carac - 1;
    }
    return 0;
}