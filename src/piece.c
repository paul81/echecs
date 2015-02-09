/**
* @copyright
* @file piece.c
* @author Boutes Paul, Cassan Damien
* @brief Implementation de toutes fonctions relative au deplacements des pieces
*/

#include "./piece.h"

GList* genererPositionPion(Case *depart, Jeu *jeu) {
    GList *position = NULL;
    const int debutBlanc = 6;
    int direction = 0;

    if (jeu->tour == 0)
    {
        direction = -1;
        if (debutBlanc == depart->ligne && !jeu->grille[depart->colonne][depart->ligne - 2].piece && !jeu->grille[depart->colonne][depart->ligne - 1].piece) {
            position = addPosition(depart->ligne - 2, depart->colonne, position);
        }
    } else {
        direction = 1;
        if (depart->ligne == 1 && !jeu->grille[depart->colonne][depart->ligne + 2].piece && !jeu->grille[depart->colonne][depart->ligne + 1].piece) {
            position = addPosition(depart->ligne + 2, depart->colonne, position);
        }
    }

    position = genererPositionPionBase(depart, jeu, direction, position);
    position = verifierPriseEnPassant(position, depart, jeu);

    return position;
}

GList* genererPositionPionBase(Case *depart, Jeu *jeu, int direction, GList *position)
{
    if (isValid(depart->ligne + 1 * direction, depart->colonne) && !jeu->grille[depart->colonne][depart->ligne + 1 * direction].piece) {
        position = addPosition(depart->ligne + 1 * direction, depart->colonne, position);
    }
    if (isValid(depart->colonne + 1, depart->ligne + 1 * direction) && jeu->grille[depart->colonne + 1][depart->ligne + 1 * direction].piece) {
        position = addPosition(depart->ligne + 1 * direction, depart->colonne + 1, position);
    }
    if (isValid(depart->colonne - 1, depart->ligne + 1 * direction) && jeu->grille[depart->colonne - 1][depart->ligne + 1 * direction].piece) {
        position = addPosition(depart->ligne + 1 * direction, depart->colonne - 1, position);
    }

    return position;
}

GList* verifierPriseEnPassant(GList *position, Case *depart, Jeu *jeu)
{
    if (jeu->tour == 0)
    {
        if (jeu->prise && depart->colonne + 1 == jeu->positionPriseCol && depart->ligne - 1 == jeu->positionPriseLigne) {
            position = addPosition(depart->ligne - 1, depart->colonne + 1, position);
        }

        if (jeu->prise && depart->colonne - 1 == jeu->positionPriseCol && depart->ligne - 1 == jeu->positionPriseLigne) {
            position = addPosition(depart->ligne - 1, depart->colonne - 1, position);
        }
    } else {
        if (jeu->prise && depart->colonne + 1 == jeu->positionPriseCol && depart->ligne + 1 == jeu->positionPriseLigne) {
            position = addPosition(depart->ligne + 1, depart->colonne + 1, position);
        }

        if (jeu->prise && depart->colonne - 1 == jeu->positionPriseCol && depart->ligne + 1 == jeu->positionPriseLigne) {
            position = addPosition(depart->ligne + 1, depart->colonne - 1, position);
        }
    }

    return position;
}


GList* genererPositionTour(Case *depart, Jeu *jeu) {
    GList *position = NULL;

    position = genererPositionTourVertical(jeu, depart, position);
    position = genererPositionTourHorizontal(jeu, depart, position);

    return position;
}

GList* genererPositionTourVertical(Jeu* jeu, Case* depart, GList *position)
{
    int i = 0;
    const int taille = 7;
    i = depart->ligne - 1;
    while (i >= depart->ligne - taille) {
        if (isValid(depart->colonne, i)) {
            position = addPosition(i, depart->colonne, position);
            if (jeu->grille[depart->colonne][i].piece) {
                i = depart->ligne - 8;
            }
        }
        i--;
    }
    i = depart->ligne + 1;
    while (i <= depart->ligne + taille) {
        if (isValid(depart->colonne, i)) {
            position = addPosition(i, depart->colonne, position);
            if (jeu->grille[depart->colonne][i].piece) {
                i = depart->ligne + 8;
            }
        }
        i++;
    }
    return position;
}

GList* genererPositionTourHorizontal(Jeu* jeu, Case* depart, GList *position)
{
    int i = 0;
    const int taille = 7;
    i = depart->colonne - 1;
    while (i >= depart->colonne - taille) {
        if (isValid(i, depart->ligne)) {
            position = addPosition(depart->ligne, i, position);
            if (jeu->grille[i][depart->ligne].piece) {
                i = depart->colonne - 8;
            }
        }
        i--;
    }
    i = depart->colonne + 1;
    while (i <= depart->colonne + taille) {
        if (isValid(i, depart->ligne)) {
            position = addPosition(depart->ligne, i, position);
            if (jeu->grille[i][depart->ligne].piece) {
                i = depart->colonne + 8;
            }
        }
        i++;
    }
    return position;
}


gboolean isValid(int colonne, int ligne) {
    const int taille = 7;
    return (colonne >=0 && ligne >=0 && colonne <= taille && ligne <= taille);
}


GList* genererPositionFouBas(Case *depart, Jeu *jeu, GList *position, int direction) {
    const int taille = 7;
    int j = 1;
    int i = depart->ligne - 1;

    while (i >= depart->ligne - taille) {
        if (isValid(depart->colonne + j * direction, i)) {
            position = addPosition(i, depart->colonne + j * direction, position);
            if (jeu->grille[depart->colonne+j * direction][i].piece) {
                i = depart->ligne - 8;
            }
        }
        j++;
        i--;
    }

    return position;
}

GList* genererPositionFouHaut(Case *depart, Jeu *jeu, GList *position, int direction) {
    int j = 1;
    int i = depart->ligne + 1;
    const int taille = 7;

    while (i <= depart->ligne + taille) {
        if (isValid(depart->colonne + j * direction, i)) {
            position = addPosition(i, depart->colonne + j * direction, position);
            if (jeu->grille[depart->colonne+j*direction][i].piece) {
                i = depart->ligne + 8;
            }
        }
        j++;
        i++;
    }

    return position;
}

GList* genererPositionFou(Case *depart, Jeu *jeu) {

    GList *position = NULL;

    position = genererPositionFouBas(depart, jeu, position, 1);
    position = genererPositionFouBas(depart, jeu, position, -1);
    position = genererPositionFouHaut(depart, jeu, position, 1);
    position = genererPositionFouHaut(depart, jeu, position, -1);

    return position;

}


GList* genererPositionRoi(Case *depart, Jeu *jeu) {
    GList *position = NULL;
    position = addPosition(depart->ligne - 1, depart->colonne, position);
    position = addPosition(depart->ligne - 1, depart->colonne + 1, position);
    position = addPosition(depart->ligne - 1, depart->colonne - 1, position);
    position = addPosition(depart->ligne, depart->colonne - 1, position);
    position = addPosition(depart->ligne, depart->colonne + 1, position);
    position = addPosition(depart->ligne + 1, depart->colonne, position);
    position = addPosition(depart->ligne + 1, depart->colonne + 1, position);
    position = addPosition(depart->ligne + 1, depart->colonne - 1, position);

    return position;
}

GList* genererPositionCavalier(Case *depart) {
    GList *position = NULL;
    position = addPosition(depart->ligne - 2, depart->colonne + 1, position);
    position = addPosition(depart->ligne - 1, depart->colonne + 2, position);
    position = addPosition(depart->ligne + 1, depart->colonne + 2, position);
    position = addPosition(depart->ligne + 2, depart->colonne + 1, position);
    position = addPosition(depart->ligne + 2, depart->colonne - 1, position);
    position = addPosition(depart->ligne + 1, depart->colonne - 2, position);
    position = addPosition(depart->ligne - 1, depart->colonne - 2, position);
    position = addPosition(depart->ligne - 2, depart->colonne - 1, position);
    return position;
}



GList* addPosition(int ligne, int colonne, GList *list) {
    Position *pos = malloc(sizeof(Position));
    pos->ligne = ligne;
    pos->colonne = colonne;
    list = g_list_append(list, pos);
    return list;
}








GList* genererPositionPiece(Case *depart, Jeu *jeu, GList *position)
{
    switch (depart->piece->type) {
        case 'P':
            position = genererPositionPion(depart, jeu);
            break;
        case 'T':
            position = genererPositionTour(depart, jeu);
            break;
        case 'F':
            position = genererPositionFou(depart, jeu);
            break;
        case 'R':
            position = genererPositionRoi(depart, jeu);
            break;
        case 'D':
            position = g_list_concat(genererPositionTour(depart, jeu), genererPositionFou(depart, jeu));
            break;
        case 'C':
            position = genererPositionCavalier(depart);
            break;
        default:
            printf("Cette piece n'existe pas");
            break;
    } return position;
}