#include "saisir_entiers.h"
#include "contenu_fichier.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

static int convertirChaine(const char *str, int *n) {
    char *end;
    *n = strtol(str, &end, 10);
    /* chaine vide ou la chaine entière ne représente pas un entier */
    if (str == end || *end != '\0') {
        return 1;
    }
    return 0;
}

static size_t valeurRetourSaisirEntiers(const size_t saisis) {
    switch (errno) {
        case ERANGE:
        case ENOMEM:
        case EINVAL:
            return -1;
        case EIO:
        default:
            return saisis;
    }
}

static int gereOptions(const Option opt, size_t *nb_lus) {
    switch (opt) {
        case RECOMMENCER:
            *nb_lus = 0;
        case REPRENDRE:
            return 1;
        default:
            return 0;
    }
}

size_t saisirEntiers(FILE *f, int *entiers, const size_t nb_attendus, Option opt) {
    int n;
    long nb_carac = 0;
    size_t t_ligne = 0, nb_lus = 0;
    char *token = NULL, *ligne = NULL;
    const char *separateurs = " \t\n";
    
    if (entiers == NULL || nb_attendus < 0) {
        errno = EINVAL;
        return -1;
    }
    
    while (nb_lus < nb_attendus) {
        errno = 0;
        nb_carac = contenuFichier(&ligne, &t_ligne, f, 1);
        if (nb_carac < 0) {
            /* si on a atteint la fin du fichier */
            if (errno == EIO && gereOptions(opt, &nb_lus)) {
                /* Permet d'enlever EOF du fichier, peut provoquer une boucle
                infinie si la saisie ne se fait pas au clavier et qu'il ne reste
                plus rien à lire dans le fichier. */
                clearerr(f);
                /* Peut servir si on modifie le fichier pour qu'il contienne une saisie valide
                (évite une boucle infinie). */
                /* if (fseek(f, 0, SEEK_SET) == -1) break; */
                continue;
            }
            break;
        }
        
        token = strtok(ligne, separateurs);
        if (token == NULL && nb_lus < nb_attendus) {
            if (gereOptions(opt, &nb_lus)) {
                continue;
            }
            break;
        }
        
        while (token != NULL) {
            /* incrémentation pour signaler que le fichier n'est pas vide */
            if (convertirChaine(token, &n) || (nb_lus == nb_attendus && nb_lus++)) {
                if (gereOptions(opt, &nb_lus)) {
                    /* si nb_lus > nb_attendus, l'entier en trop ne sera pas stockés dans le tableau */
                    break;
                }
                errno = EIO;
                free(ligne);
                return valeurRetourSaisirEntiers(nb_lus);
            }
            entiers[nb_lus] = n;
            nb_lus++;
            token = strtok(NULL, separateurs);
        }
    }
    free(ligne);
    return valeurRetourSaisirEntiers(nb_lus);
}