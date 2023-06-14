#include "contenu_fichier.h"
#include "saisir_nom.h"
#include "saisir_fichier.h"
#include "saisir_entiers.h"
#include <stdlib.h>
#include <stdio.h>

static int test_contenuFichier() {
    char *ln = NULL;
    int val_retour = 1;
    size_t n = 0;
    long p = contenuFichier(&ln, &n, stdin, 0);
    if (p != -1) {
        printf("(lenstr: %ld, lenbuff: %ld) %s", p, n, ln);
        val_retour = 0;
    }
    free(ln);
    return val_retour;
}

static int test_saisirFichier() {
    FILE *f;
    if (ouvreFichier(&f, "./toto.txt", ".txt", "r")) {
        return 1;
    }
    return 0;
}

static int test_saisirNom() {
    char *ln = NULL;
    int val_retour = 1;
    size_t n = 0;
    if (!saisirNom(stdin, &ln, &n)) {
        printf("(taille %ld) %s\n", n, ln);
        val_retour = 0;
    }
    free(ln);
    return val_retour;
}

static int test_saisirEntiers() {
    const int t_tab = 2;
    int *tab = calloc(t_tab, sizeof(int));
    /* int tab[2]; */
    int i = 0;
    printf("valeur de retour saisis: %ld\n", saisirEntiers(stdin, tab, t_tab, RECOMMENCER));
    for (; i < t_tab; i++) {
        printf("%d\n", tab[i]);
    }
    free(tab);
    return 0;
}

int main() {
    test_contenuFichier();
    test_saisirFichier();
    test_saisirNom();
    test_saisirEntiers();
    return 0;
}