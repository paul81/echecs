# Implémentation du déplacement

## Prototypes

```
/**
 * Permet d'effectuer le déplacement d'une pièce
 * 
 * g : Représente la grille du jeu, l'échiquier
 * depart :  Représente la case de départ de la pièce à déplacer
 * arrive :  Représente la case d'arrivée de la pièce déplacée
 * j : Représente le joueur
 *
 * retourne 0 si tout va bien, sinon un code d'erreur
 */

int deplacer(Grille* g,Case depart, Case arrive, Joueur* j);

```

```
/**
 * Génère la liste des positions possibles pour une pièce
 * 
 * depart : Représente la case de la pièce a déplacer
 * retourne une Liste de doublé des positions possibles pour une pièce
 */     

GList* genererPosition(Case depart);

```

```
/**
 * Vérifie les positions valide dans la GList* listePosition
 * 
 * listePosition : liste de doublé contenant toutes les positions possibles pour une pièce
 *  g : Représente la grille du jeu
 *  j : Représente un joueur 
 *  retourne la liste des déplacements valide (enlève les déplacements hors de la grille et sur les pions alliés)
 */

GList* check(GList* listePosition, Grille* g, Joueur* j);

```

```

/**
 * Permet de mettre à jour les pièces déplacés et/ou mangés
 * 
 *  g : Représente la grille du jeu 
 *  listePosition :  liste de doublé contenant toutes les positions possibles pour une pièce
 *  depart : Représente la case de départ de la pièce 
 *  arrive : Représente la case d'arrivée de la pièce 
 *  j : Représente le joueur qui déplace sa pièce
 *
 */

void effectuerDeplacement(Grille* g, Glist* listePosition, Case depart, Case arrive, Joueur* j);

```


```
/**
 * Permet d'annuler un déplacement d'une pièce
 * 
 * pieceDeplace : Représente la pièce qui a été déplacé
 * caseCible : Représente la case sur laquelle la pièce déplacé se trouvait
 * g : Représente la grille du jeu 
 * depart : Représente la case d'origine de la pièce déplacé
 */

void annulerDeplacement(Piece* pieceDeplace, Case* caseCible, Grille* g, Case* depart);

```

```

/**
 * Permet d'annuler la prise de la pièce
 * 
 * piecePrise : Représente la pièce qui a été prisee
 * arrive : Représente la case sur laquelle était placé piecePrise
 * j : Représente le joueur
 */

void annulerPrise(Piece* piecePrise, Case* arrive, Joueur* j);

```

```
/**
 * Permet de vérifier si le joueur j est en echec
 * On génère toutes les positions possibles des pièces, et on compare avec la liste de pièces du joueur

 * j : Représente le Joueur avec sa liste de pièce 
 * retourne vrai si le joueur est en echec, sinon retourne non
 */

bool isEchec(Joueur* j);

```


## Pseudo-code

```

int deplacer(Grille* g,Case *depart, Case *arrive, Joueur* j) {
    GList *p;
    p <- genererPosition(depart);
    p <- check(p,g,j);

    if (arrive in p) {
        Piece *pieceDeplacer;
        Piece *piecePrise = NULL;

        effectuerDeplacement(g,p,depart,arrive,j);

        if (isEchec(j)) {
            annulerDeplacement(pieceDeplace, arrive, g, depart);

            if (piecePrise) {
                annulerPrise(piecePrise, arrive, j);
            }

            return 1;
        }

    }
    return 0;
}



```