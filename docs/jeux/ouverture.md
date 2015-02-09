# Ouverture

Les ouvertures sont des stratétegies de jeux utilisées en debut de parties, elle permettent notamment de bien positioner ses pièces et de placer les rois en securités. Il existe une multitude d'ouvertures et pour chacune d'entre-elles plusieurs variantes, elle sont souvent nommé en fonction de leur inventeur.

On utilise la notation algebrique pour définir les ouvertures. Les deplacements dans la colonne de gauche correspondent aux mouvements des piéces blanches et ceux de la colonne de droite aux piéces de couleurs noires.

## Implementation

Pour implémenter les bases de données d'ouverture nous avons choisis d'utiliser une table de hachage. Un etat de l'échiquier sera donc réprésenté par un hash et l'IA cherchera la correspondance entre l'etat actuel de l'échiquier et une ouverture dans la base de données.

Format d'un hash :

(Initiale de la piéce - position sous la forme algebrique) (suivant) ..

Example :

RA1 DA3 FB2 CC4

Correspond à :

- Roi en position A1;
- Dame en position A3;
- Fou en position B2;
- Cavalier en position C4.

Il faut respecter l'ordre dans lequelle sont placés les piéces dans le hash afin que deux états identique aient toujours le même hash. On définira donc l'ordre suivant :

Roi - Dame - Fou - Tour - Cavalier - Pion

Il faut aussi définir un ordre pour les piéces de même types. On peut par exemple définir un ordre pour les cases :

Suggestions :
    - On compare les lettres A < B < C ...;
    - Puis le nombre 1 < 2;
    - ->  A8 < B2 < C3 < C6.

On aura donc bessoin : 

- D'une fonction comparant deux cases;
- D'une fonction prenant une liste de piéce et renvoyant un hash.


## Defense Indienne 

Cette strategie permet de sécuriser la position de la reine pour le joueur ayant les piéces noires.

  
1. : d4     Cf6
2. : c4     e6
3. : Cf3    b6

## Defense Benoni

  
1. : d4     Cf6
2. : c4     c5

## Le mat du berger

Cette ouverture permet d'effectuer un echec et mat en seulement 4 tours.

   
1. : e4     e5
2. : Dh5    Cc6
3. : Fc4    Cf6
4. : Df7 -> Mat

## La croisade du cavalier

1. : d4 Cf6
2. : Cd2 e5
3. : de5 Cg4
4. : h3  Ce3