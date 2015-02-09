# Sauvegarde

Le programme doit pouvoir sauvegarder l'etat d'une partie dans un fichier de façon a pouvoir reprendre la partie entre chaque execution du programme.

## Structure du fichier

Nous devons stocker les données suivantes :

- Les piéces :
    + positions
    + type
    + appartenance joueurs
- l'avancement
    + tours
- les joueurs : 
    + prisePassant

Nous avons donc choisie de le modéliser de la facon suivante :

```
{
    'Partie': {
        'Nombre de tours' : n,
        'PrisePassant': true/false,
        'PositionPrisePassant': 'A1 '
    },
    'Joueurs1': {
        'Hash': 'RA1DB2PA2...'
    },
    'Joueurs2': {
        'Hash': 'CA3....'
    }
}

```

Modelisation binaire :
```
   Tours : char
   PrisePassant : char
   PositionPrisePassant : 2 * char (si PrisePassant == 1)
   HashJoueur1 : x * char
   Separateur (';') : char
   HashJoueur2 : y * char
   Separateur (';') : char
```

# Implementation

Deux choix on été retenue pour implémenter cette sauvegarde :

- Fichier Binaire
    + Avantage : 
        * Rapide à parcourir
        * Petite taille du fichier
    + Incovenient
        * Implementation
        
- Fichier JSON
    + Avantage
        * Lecture facile
        * Facilement utilisable par d'autres programmes
        * Implementer par jsonGlib
    + Incovenient
        * Taille importante des fichiers

## Prototype

```
/**
 * Permet de sauvegarder dans un fichier l'état du jeu
 * 
 * fichier : Nom du fichier qui va être enregistré
 * jeu : Structure regroupant les joueurs, le tour, et la grille de l'échiquier
 * 
 * retourne 0 si tout va bien, sinon un code d'erreur si le fichier ne s'est pas enregistré
 */

int sauvegarder(char* fichier,Jeu* jeu);

```


```
/**
 * Permet d'ouvrir un fichier et d'initialiser les variables associées
 * 
 * fichier : Nom du fichier qui va être chargé
 * jeu : Structure regroupant les joueurs, le tour, et la grille de l'échiquier
 * 
 * retourne 0 si tout va bien, sinon retourne un code d'erreur s'il y a une erreur lors du chargement du fichier
 */

int ouvrir(char* fichier, Jeu* jeu);

```


