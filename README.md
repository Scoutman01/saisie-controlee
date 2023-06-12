> Dans l'univers complexe des logiciels, une vérité demeure : il ne faut jamais placer une confiance absolue en l'utilisateur.
> Comme les vagues imprévisibles de l'océan, les saisies de l'utilisateur peuvent cacher des pièges sournois. C'est en anticipant les
> écarts et en validant chaque entrée que le code s'élève, protégeant ainsi les horizons numériques des naufrages inattendus.
>
> -- <cite>ChatGPT</cite>

L'objectif est d'étudier plusieurs langages de programmation afin d'explorer les meilleures pratiques pour réaliser une saisie
contrôlée, garantissant la sécurité maximale, sans implémenter des fonctionnalités déjà existantes (par
exemple pour la gestion des arguments de ligne de commande : getopt en C, argparse en Python, etc).

La principale contrainte consiste à n'utiliser qu'exclusivement la bibliothèque standard du langage,
pas de bibliothèques externes ou d'extensions, sauf peut-être quelques normes comme POSIX pour le langage C puisque les
systèmes de fichiers varient selon les plateformes.

La portabilité est un plus, mais les programmes sont uniquement testés sur Linux.

## Les différentes saisies :

- Entrer exactement un nombre spécifié d'entiers (sur une ou plusieurs lignes). Si la saisie n'est pas bonne, on a alors
plusieurs choix : quitter la saisie (par défaut), recommencer la saisie depuis le début, recommencer la saisie à partir de la dernière valeur
correcte. Les entiers saisis seront stockés dans un tableau. Les espaces, tabulations et retours à la ligne sont ignorés.
    
    Par exemple, on demande de saisir 3 entiers, les entrées suivantes sont valides :
    ```
    $>1 2
    3

    $>1
    2
    3

    $>1 2 3
    ```
    Les entrées suivantes ne sont pas valides :
    ```
    $>1 2 3 4
    $>1 2 3 a
    $>a 1 2 3
    ```
    La fonction aura pour valeur de retour :
    - -1, les arguments de la fonction ne sont pas bons, erreur d'allocation, dépassement de capacité
    - sinon le nombre d'entiers lus
- Entrer un nom/pseudonyme d'une longueur maximale spécifique, composé uniquement de caractères alphanumériques.
- Fournir le nom d'un fichier (avec ou sans extension), qui puisse être ouvrable et accessible dans un mode d'ouverture spécifié