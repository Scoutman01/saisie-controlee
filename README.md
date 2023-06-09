> Dans l'univers complexe des logiciels, une vérité demeure : il ne faut jamais placer une confiance absolue en l'utilisateur.
> Comme les vagues imprévisibles de l'océan, les saisies de l'utilisateur peuvent cacher des pièges sournois. C'est en anticipant les
> écarts et en validant chaque entrée que le code s'élève, protégeant ainsi les horizons numériques des naufrages inattendus.
>
> -- <cite>ChatGPT</cite>

L'objectif est d'étudier plusieurs langages de programmation afin d'explorer les meilleures pratiques pour réaliser une saisie
contrôlée, garantissant la sécurité maximale, sans dépendre des fonctionnalités déjà fournies par les bibliothèques existantes (par
exemple pour la gestion des arguments de ligne de commande : getopt en C, argparse en Python, etc).

La principale contrainte consiste à n'utiliser qu'exclusivement la bibliothèque standard du langage,
pas de bibliothèques externes ou d'extensions.

## Les différentes saisies :

- Entrer exactement un nombre spécifié d'entiers
- Entrer un nom/pseudonyme d'une longueur maximale spécifique, composé uniquement de caractères alphanumériques.
- Fournir le nom d'un fichier pouvant être ouvert et accessible en lecture/écriture (mode d'ouverture r+)