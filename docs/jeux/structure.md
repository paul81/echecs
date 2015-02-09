# Implémentation du jeu

Pour réaliser ce projet, nous devons penser aux différentes structures, types de données que nous allons utilisés dans notre projet.

## Structures de données

### Représentation de l'échiquier

Pour pouvoir réprésenter l'échiquier, nous allons implémenter une structure représentant les cases de l'échiquier.

La structure "Case" sera donc la suivante : 
```
struct Case {
     int colonne;
     int ligne;
     Piece *piece;
}
```

* L'entier colonne représente une colone de l'échiquier;
* L'entier ligne représente une ligne de l'échiquier;
* La structure Piece représente la pièce présente sur la case à la position colonne et ligne.

La structure "Piece" sera donc la suivante : 
```
struct Piece {
    char type;
    Case *case;
    Joueur *joueur;
}
```

* Le char type représente le type de la pièce (pion, roi, dame, fou, tour);
* La *case représente la case sur laquelle se trouve la pièce.
* La *joueur permet d'avoir les différentes informations du joueur à qui appartient la pièce. 


De ce fait, grâce à ces deux structures, nous pouvons représenter la grille de notre échiquier. 

La grille est donc : 
    ```
        typedef Grille Case[8][8];
    ```

Grâce à cette représentation, nous avons facilement accès aux pièces présentent sur une case, ou à l'inverse, à la position d'une pièce dans la grille.


### Représentation du joueur

De plus nous utiliserons une liste de Pièce qui va donc contenir les différentes pièces encore présentent sur la grille, ce qui va nous être utile pour effectuer des opérations sur l'ensemble des pièces, sans faire de parcours inutile à partir de la grille. 
Par exemple, le calcul de l'echec, ou du pat.
Cette liste va être rattaché au joueur, pour indiquer les pièces du joueur présente sur l'échiquier.

La structure "Joueur" sera donc la suivante : 

```

struct Joueur {
    int id;
    GList *listePieces;
    Piece *roi;
    Joueur* adverse;
    bool PrisePassant;
    Case *positionPrisePassant;
}

```

* L'entier id représente le joueur 1 ou le joueur 2;
* La Glist* listePieces représente la liste des pièces sur l'échiquier de joueur;
* La Piece* roi permet de garder la position du roi en mémoire, pour calculer l'échec, et le pat plus rapidement;
* Le Joueur* adverse permet d'avoir accès aux données du joueur adverse durant la partie;
* Le booleen PrisePassant indique s'il est possible pour le joueur adverse d'effectuer une prise en passant pour le tour actuel.
* La Case* positionPrisePassant permet de retenir l'endroit où il est possible d'effectuer une prise en passant.


### Représentation du jeu

Pour représenter les différentes variables du jeu, nous allons les regroupés dans une structure Jeu, qui va donc être : 

```
struct Jeu {
    Joueur* blanc;
    Joueur* noir;
    int tour;
    Grille* grille;
}

```

* Le Joueur* blanc représente les pièces blanche;
* Le Joueur* noir représente les pièces noires;
* L'entier indique quel joueur doit jouer;
* La Grille* grille représente la grille de l'échiquier.

