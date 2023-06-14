#include "saisir_entiers.h"
#include "contenu_fichier.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/**
 * Convertit une chaîne de caractères en un entier.
 * 
 * @param str une chaine de caractères, qui représente un entier en base 10.
 * @param n pointeur vers un entier, contiendra l'entier converti depuis la chaine de caractères.
 * 
 * @return int, renvoie 1 si la chaine d'entrée est vide ou ne représente pas un entier, sinon renvoie 0.
 */
static int convertirChaine(const char *str, int *n) {
    char *end;
    *n = strtol(str, &end, 10);
    /* chaine vide ou la chaine entière ne représente pas un entier */
    if (str == end || *end != '\0') {
        return 1;
    }
    return 0;
}

/**
 * @brief Détermine la valeur de retour de la saisie.
 * 
 * @param nb_lus size_t, le nombre d'entiers lus
 * @return long, renvoie le nombre d'entiers lus, ou renvoie -1 si une erreur s'est
 * produit lors de la saisie.
 */
static long valeurRetourSaisirEntiers(const size_t nb_lus) {
    switch (errno) {
        case ERANGE:
        case ENOMEM:
        case EINVAL:
        case ESPIPE: /* fseek */
            return -1;
        case EIO:
        default:
            return nb_lus;
    }
}

/**
 * @brief Détermine le comportement de la saisie en fonction de l'option
 * choisie lorsqu'une erreur de saisie se produit.
 * 
 * @param nb_lus size_t, le nombre d'entiers lus.
 * @param opt Option, comportement à adopter lorsqu'une erreur de saisie se produit.
 * @return int, renvoie 0 si la saisie se termine directement, renvoie 1 sinon.
 */
static int gereOptions(size_t *nb_lus, const Option opt) {
    switch (opt) {
        case RECOMMENCER:
            *nb_lus = 0;
        case REPRENDRE:
            return 1;
        default:
            return 0;
    }
}

long saisirEntiers(FILE *f, int *entiers, const size_t nb_attendus, Option opt) {
    int n;
    long nb_carac;
    size_t t_ligne = 0, nb_lus = 0;
    char *token = NULL, *ligne = NULL;
    const char *separateurs = " \t\r\n";
    
    if (entiers == NULL) {
        errno = EINVAL;
        return -1;
    }
    
    while (nb_lus < nb_attendus) {
        nb_carac = contenuFichier(&ligne, &t_ligne, f, 1);
        if (nb_carac < 0) {
            /* si on a atteint la fin du fichier */
            if (errno == EIO && gereOptions(&nb_lus, opt)) {
                errno = 0;
                /* Permet d'enlever EOF du fichier, peut provoquer une boucle
                infinie si la saisie ne se fait pas au clavier et qu'il ne reste
                plus rien à lire dans le fichier. */
                clearerr(f);
                /* Peut servir si on modifie le fichier pendant l'exécution du programme
                pour qu'il contienne une saisie valide (évite une boucle infinie). */
                /* if (fseek(f, 0, SEEK_SET) == -1) break; */
                continue;
            }
            break;
        }
        
        token = strtok(ligne, separateurs);
        if (token == NULL) {
            if (gereOptions(&nb_lus, opt)) {
                continue;
            }
            break;
        }
        
        while (token != NULL) {
            /* incrémentation pour signaler que le fichier n'est pas vide */
            if (convertirChaine(token, &n) || (nb_lus == nb_attendus && ++nb_lus)) {
                if (gereOptions(&nb_lus, opt)) {
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