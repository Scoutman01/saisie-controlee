#define _GNU_SOURCE /* pour utiliser getline qui n'est pas standard */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TAILLE_MAX_NOM 19


/**
 * @brief Effectue une saisie contrôlée de deux entiers et les affiche sur la sortie standard.
 * N'importe quel entier est valide. Etant donné que la fonction utilise seulement la valeur de retour
 * de scanf comme indicateur de réussite de la saisie, seuls les deux premiers champs saisis sont vérifiées.
 * 
 * la saisie marche si on entre :
 * 1 2
 * -33 -65
 * 1 2 a 
 * 1 2 3 4 5
 * 1 2 a b c
 * 
 * la saisie ne marche pas si on entre :
 * a 1
 * 1 b
 * 1 a 2
 * a 1 2
 */
void saisie_entier() {
    int a, b, verif, c;
    do {
        printf("Veuillez saisir deux entiers : ");
        verif = scanf("%d %d", &a, &b);
        if (verif != 2)
            while((c = getchar()) && c != '\n'); /* vide le contenu de stdin */
    } while(verif != 2);
    printf("Vous avez saisie %d et %d\n", a, b); 
}

/**
 * @brief Compte le nombre de mots dans une chaine de caractères
 * 
 * @param mot char*, chaine de caractères
 * @return int, nombre de mots
 */
int compteMots(char * chaine) {
    int nbmots, espace;
    int c;
    if (!chaine) /* pointeur NULL */
        return 0;
    nbmots = 0;
    espace = 0;
    for (c = 0; chaine[c] != '\0'; c++) {
        if (chaine[c] == '\t' || chaine[c] == '\n' || chaine[c] == ' ') {
            nbmots += espace;
            espace = 0;
        }
        else
            espace = 1;
    }
    return (espace ? nbmots + 1 : nbmots);
}

/* la saisie ne marche pas si on entre 1 2 a */
void saisie_entier_deux() {
    int a, b, verif, verifmots;
    char *ligne;
    size_t len;
    len = 0;
    ligne = NULL;
    do {
        printf("Veuillez saisir deux entiers : ");
        getline(&ligne, &len, stdin);
        verifmots = compteMots(ligne);
        if (verifmots != 2)
            printf("Trop de champs saisie (%d)\n", verifmots);
        else
            verif = sscanf(ligne, "%d %d", &a, &b);
    } while(verif != 2);
    printf("Vous avez saisie : %d et %d\n", a, b);
    free(ligne);
}

int caractere_valide(char * mot) {
    int i;
    for (i = 0; mot[i]; i++) {
        if (!isalnum(mot[i]))
            return 0;
    }
    return 1;
}

void saisie_nom() {
    int verif;
    char * nom;
    size_t len;
    ssize_t nbcarac;
    len = 0;
    verif = 0;
    nbcarac = 0;
    nom = NULL;
    do {
        printf("Veuillez saisir votre nom (max : %d caractères) : ", TAILLE_MAX_NOM);
        nbcarac = getline(&nom, &len, stdin);
        if (nbcarac < 0) { /* EOF */
            free(nom);
            return;
        }
        if (!nom) /* l'allocation s'est mal passée */
            return;
        nom[nbcarac - 1] = '\0'; /* on enlève le '\n' */
        nbcarac--;
        if (!caractere_valide(nom))
            printf("Le nom doit etre composee uniquement de caracteres alphanumerique\n");
        else if (nbcarac > 0 && nbcarac <= TAILLE_MAX_NOM)
            verif = 1;
        else {
            printf("Nom trop %s (%zd)\n", nbcarac == 0 ? "court" : "long", nbcarac);
            nom[0] = '\0';
        }
    } while(verif != 1);
    printf("Votre nom est : %s\n", nom);
    free(nom);
}

void saisie_nom_deux() {
    char car, *chaine, *tmp;
    int t_max, t_reelle, verif;
    t_reelle = 0;
    t_max = 2;
    chaine = (char *) malloc(sizeof(char) * t_max);
    if (chaine == NULL) {
        fprintf(stderr, "malloc erreur allocation\n");
        return;
    }
    verif = scanf(" %c", &car);
    if (verif == 0 || verif == EOF) {
        free(chaine);
        return;
    }
    chaine[t_reelle++] = car;
    car = getchar();
    while (car != '\n') {
        if (t_reelle + 1 >= t_max) {
            t_max *= 2;
            /* Augmentation de la taille de la chaine */
            tmp = (char *) realloc(chaine, t_max);
            if (tmp == NULL) {
                err_realloc:
                    fprintf(stderr, "realloc erreur allocation\n");
                    free(chaine);
                    return;
            }
            chaine = tmp;
        }
        chaine[t_reelle++] = car;
        car = getchar();
    }
    chaine[t_reelle] = '\0';
    tmp = (char *) realloc(chaine, t_reelle + 1); /* Taille réelle de la chaine, + 1 pour "\0" */
    if (tmp == NULL)
        goto err_realloc;
    chaine = tmp;
    printf("%s\n", chaine);
    printf("taille = %d\n", t_reelle);
    free(chaine);
}

int main() {
    //saisie_entier();
    //saisie_entier_deux();
    //saisie_nom();
    saisie_nom_deux();
    return 0;
}