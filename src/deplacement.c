/**
 * @copyright 

 * @file deplacement.c
 * @author Boutes Paul, Cassan Damien
 * @brief Contient les fonctions permettant de gérer les déplacements des pions dans le jeu 
 */


#include <t1tables.h>
#include "./deplacement.h"

GList* genererPosition(Case *depart, Jeu *jeu) {
    GList *position = NULL;

    position = genererPositionPiece(depart, jeu, position);
    position = check(position, jeu);

    return position;
}

int effectuerEchetEtMat(Jeu *jeu)
{
    int retour = 0;

    if (isEchec(jeu, jeu->tour))
    {
        printf("fin du jeu : echecs et mat \n");
        retour = 100 + jeu->tour;
    } else {
        printf("fin du jeu : pat \n");
        retour = 102 + jeu->tour;
    }

    return retour;
}

int verifieEchecEtMat(Jeu *jeu, GList* positions) {
    GList *iterateur = NULL;
    GList *allPositions = NULL;
    Piece* piece = NULL;
    int retour = 1;
    if (jeu->tour == 0) {
        iterateur = jeu->blanc->pieces;
    } else {
        iterateur = jeu->noir->pieces;
    }
    while(iterateur) {
        piece = (Piece*)iterateur->data;
        positions = genererPosition(piece->casePiece, jeu);
        positions = check(positions, jeu);
        positions = checkEchec(piece->casePiece, positions, jeu);
        allPositions = g_list_concat(allPositions, positions);
        iterateur = iterateur->next;
    }
    if (g_list_length(allPositions) == 0) {
        retour = effectuerEchetEtMat(jeu);
    }
    return retour;
}

void annulerRoque(Jeu *jeu, Case *depart) {
    if (depart->piece->type == 'T') {
        if (jeu->tour == 0) {
            if (depart->colonne == 0) {
                jeu->positionInitialeTour1Blanc = 0;
            } if (depart->colonne == 7) {
                jeu->positionInitialeTour2Blanc = 0;
            }
        } else {
            if (depart->colonne == 0) {
                jeu->positionInitialeTour1Noir = 0;
            } if (depart->colonne == 7) {
                jeu->positionInitialeTour2Noir = 0;
            }
        }
    } if (depart->piece->type == 'R') {
        if (jeu->tour == 0) {
            jeu->positionInitialeTour1Blanc = 0;
            jeu->positionInitialeTour2Blanc = 0;
        } else {
            jeu->positionInitialeTour1Noir = 0;
            jeu->positionInitialeTour2Noir = 0;
        }
    }
}

void activerPrisePassant(Jeu *jeu, Case *depart, Case *arrive)
{
    if (arrive->piece->type == 'P') {

        if (jeu->tour == 0 && arrive->ligne == 4 && depart->ligne == 6) {
            jeu->prise = 1;
            jeu->positionPriseLigne = (char) depart->ligne - (char) 1;
            jeu->positionPriseCol = (char) depart->colonne;
        } else if (jeu->tour == 1 && arrive->ligne == 3 && depart->ligne == 1) {
            jeu->prise = 1;
            jeu->positionPriseLigne = (char) depart->ligne + (char) 1;
            jeu->positionPriseCol = (char) depart->colonne;
        } else {
            /*Pas de prise en passant possible*/
        }
    }
}

int verifierDeplacement (Jeu* jeu, GList* iterateur, Case *arrive, Case *depart)
{
    int retour = 1;
    Position *pos;
    pos = (Position *) iterateur->data;
    if (pos->ligne == arrive->ligne && pos->colonne == arrive->colonne) {
        annulerRoque(jeu, depart);
        effectuerDeplacement(jeu, depart, arrive);
        retour = 0;
        jeu->prise = 0;
        if (jeu->tour == 0 && arrive->ligne == 0 && arrive->piece->type == 'P') {
            retour = 300 + jeu->tour;
        } if (jeu->tour == 1 && arrive->ligne == 7 && arrive->piece->type == 'P') {
            retour = 300 + jeu->tour;
        }
        activerPrisePassant(jeu, depart, arrive);
        if (jeu->tour) {
            jeu->tour = 0;
        } else {
            jeu->tour = 1;
        }
        printf("Deplacement effectué  \n");
    }
    return retour;
}

int trouverDeplacement(Jeu *jeu, Case *depart, Case *arrive)
{
    int retour = 1;
    GList *positions = NULL;
    GList *iterateur = NULL;
    positions = genererPosition(depart, jeu);
    positions = checkEchec(depart, positions, jeu);
    iterateur = positions;

    if (g_list_length(positions) == 0)
    {
        retour = verifieEchecEtMat(jeu, positions);
    } else {
        retour = effectuerRoque(depart, arrive, jeu);
        while (iterateur && retour == 1) {
            retour = verifierDeplacement(jeu, iterateur, arrive, depart);
            iterateur = iterateur->next;
        }
    }
    if (positions) {
        g_list_free_full(positions, &freeElement);
        positions = NULL;
    }
    return retour;
}


int updateHistorique(Jeu *jeu, int retour) {
    GString *hash1;
    GString *hash2;
    GString *hash = g_string_new("");
    gboolean find = FALSE;
    int count = 0;
    gpointer key, value;
    hash1 = createHash(jeu->blanc->pieces);
    hash2 = createHash(jeu->noir->pieces);
    hash = g_string_append(hash, hash1->str);
    hash = g_string_append(hash, hash2->str);
    find = g_hash_table_lookup_extended(jeu->historique, (GString *)hash->str, &key, &value);
    if (!find) {
        ++count;
        g_hash_table_insert(jeu->historique, (GString *)hash->str, GINT_TO_POINTER(count));
    } else {
        count = GPOINTER_TO_INT(value);
        if (count < 3) {
            ++count;
            g_hash_table_insert(jeu->historique, (GString *)hash->str, GINT_TO_POINTER(count));
        } else {
            retour = 400 + jeu->tour;
            printf("Le joueur %d peut demander un match null \n", jeu->tour);
        }
    }
    return retour;
}

int deplace(Case *depart, Case *arrive, Jeu *jeu) {
        int retour = 1;
        if (!depart || !depart->piece) {
            printf("Pas de piece sur cette case !\n");
            retour = 2;
        } else if (depart->piece->joueur->id != jeu->tour) {
            printf("Cette piece ne vous appartient pas !\n");
            retour = 3;
        } else if (!arrive) {
            printf("Case d'arrivé invalide \n");
            retour = 4;
        } else {
            retour = trouverDeplacement(jeu, depart, arrive);

            if (!retour) {
                retour = updateHistorique(jeu, retour);
            }
        }
    return retour;
}

int verifierRoqueDeplacement(Case* arrive, Piece *roi, Jeu *jeu, Piece *tour, Case *parcours, Case *depart)
{
    int retour = 0;
    if (!arrive->piece) {
        arrive->piece = roi;
        depart->piece = NULL;
        roi->casePiece = arrive;
        if (isEchec(jeu, jeu->tour)) {
            arrive->piece = NULL;
            depart->piece = roi;
            roi->casePiece = depart;
        } else {
            tour->casePiece->piece = NULL;
            tour->casePiece = parcours;
            parcours->piece = tour;
            retour = 1;
        }
    }
    return retour;
}

int verifierRoque(Case *parcours, Case *depart, Case *arrive, Jeu *jeu, Piece *tour, Piece *roi) {
    int retour = 0;
    if (parcours->piece == NULL) {
        parcours->piece = roi;
        depart->piece = NULL;
        roi->casePiece = parcours;
        if (isEchec(jeu, jeu->tour)) {
            parcours->piece = NULL;
            depart->piece = roi;
            roi->casePiece = depart;
        } else {
            retour = verifierRoqueDeplacement(arrive, roi, jeu, tour, parcours, depart);
        }
    }
    return retour;
}

int validerRoque(Jeu *jeu, int direction)
{
    int retour = 0;
    if (direction && jeu->tour == 0) {
            jeu->tour = 1;
            retour = 202;
    } else if (direction && jeu->tour == 1){
            jeu->tour = 0;
            retour = 203;
    } else if (!direction && jeu->tour == 0){
            jeu->tour = 1;
            retour = 200;
    } else {
            jeu->tour = 0;
            retour = 201;
    }
    if (!jeu->tour) {
        jeu->positionInitialeTour1Noir = 0;
        jeu->positionInitialeTour2Noir = 0;
    } else {
        jeu->positionInitialeTour2Blanc = 0;
        jeu->positionInitialeTour1Blanc = 0;
    }
    g_hash_table_remove_all(jeu->historique);

    return retour;
}

GList* check(GList *position, Jeu *jeu) {
    Position *p = NULL;
    GList *next = NULL;
    GList *iterateur = position;
    const int taille = 7;
    while (iterateur) {
        p = (Position*)iterateur->data;
        next = g_list_next(iterateur);
        if (p->ligne < 0 || p->ligne > taille || p->colonne < 0 || p->colonne > taille) {
            position = g_list_delete_link(position, iterateur);
            free(p);
        } else if (jeu->grille[p->colonne][p->ligne].piece && jeu->grille[p->colonne][p->ligne].piece->joueur->id == jeu->tour) {
            free(p);
            position = g_list_delete_link(position, iterateur);
        } else {
            /* Cas par defaut */
        }
        iterateur = next;
    }
    return position;
}

int effectuerRoque(Case *depart, Case *arrive, Jeu *jeu) {
    int retour = 1;
    Piece *roi = depart->piece;
    Piece *tour = NULL;
    Case *parcours = NULL;
    if (roi && roi->type == 'R' && arrive->colonne == (depart->colonne - 2) && !jeu->grille[depart->colonne - 3][depart->ligne].piece) {
        tour = jeu->grille[arrive->colonne - 2][depart->ligne].piece;
        if ((jeu->tour == 0 && jeu->positionInitialeTour1Blanc) || (jeu->tour == 1 && jeu->positionInitialeTour1Noir)) {
            parcours = &jeu->grille[depart->colonne - 1][depart->ligne];
            if (verifierRoque(parcours, depart, arrive, jeu, tour, roi)) {
                retour = validerRoque(jeu, 0);
            }
        }
    } if (roi && roi->type == 'R' && arrive->colonne == (depart->colonne + 2)) {
        tour = jeu->grille[arrive->colonne + 1][depart->ligne].piece;
        if ((jeu->tour == 0 && jeu->positionInitialeTour2Blanc) || (jeu->tour == 1 && jeu->positionInitialeTour2Noir)){
            parcours = &jeu->grille[depart->colonne + 1][depart->ligne];
            if (verifierRoque(parcours, depart, arrive, jeu, tour, roi)) {
                retour = validerRoque(jeu, 1);
            }
        }
    }

    return retour;
}



Case* getCase(char colonne, char ligne, Jeu *jeu) {
    int a;
    int b;
    Case *res = NULL;
    a = colonne;
    b = ligne;
    res = !isValid(a, b) ? NULL : &jeu->grille[a][b];
    return res;
}




void algebrique(Move *piece, gboolean pion) {
        if (!pion) {
                printf("Deplace la pièce avec la notation algebrique %c %s - %s \n", piece->code, piece->param1->str + 1, piece->param2->str);
        } else {
                printf("Deplace la pièce avec la notation algebrique %s - %s \n", piece->param1->str, piece->param2->str);
        }
}

gboolean isEchecBlanc(Jeu *jeu) {
    GList *iterateur= NULL;
    gboolean retour = FALSE;
    Piece* piece = NULL;
    GList *position = NULL;
    Position *pos = NULL;
    jeu->tour = 1;
    iterateur = jeu->noir->pieces;
    while(iterateur) {
        piece = (Piece*)iterateur->data;
        position = g_list_concat(position, genererPosition(piece->casePiece, jeu));
        iterateur = iterateur->next;
    }
    position = check(position, jeu);
    iterateur = position;
    while (iterateur) {
        pos = (Position*)iterateur->data;
        if (pos->ligne == jeu->blanc->roi->casePiece->ligne && pos->colonne == jeu->blanc->roi->casePiece->colonne)
        {
            retour = TRUE;
        }
        iterateur = iterateur->next;
    }
    return retour;
}

gboolean isEchecNoir(Jeu *jeu)
{
    GList *iterateur= NULL;
    gboolean retour = FALSE;
    Piece* piece = NULL;
    GList *position = NULL;
    Position *pos = NULL;
    jeu->tour = 0;
    iterateur = jeu->blanc->pieces;
    while(iterateur) {
        piece = (Piece*)iterateur->data;
        position = g_list_concat(position, genererPosition(piece->casePiece, jeu));
        iterateur = iterateur->next;
    }
    iterateur = position;
    while (iterateur) {
        pos = (Position*)iterateur->data;
        if (pos->ligne == jeu->noir->roi->casePiece->ligne && pos->colonne == jeu->noir->roi->casePiece->colonne) {
            retour = TRUE;
        }
        iterateur = iterateur->next;
    }
    return retour;
}

gboolean isEchec(Jeu *jeu, char joueur)
{

    gboolean retour = FALSE;
    char tour = jeu->tour;

    if (joueur == 0) {
        retour = isEchecBlanc(jeu);

    } else {
        retour = isEchecNoir(jeu);
    }

    jeu->tour = tour;
    return retour;
}

Piece* effectuerPriseEnPassant(Jeu *jeu, Case* arriver, Piece *piecePrise)
{
    if (jeu->prise && arriver->ligne == jeu->positionPriseLigne && arriver->colonne == jeu->positionPriseCol) {
        if (!jeu->tour) {
            piecePrise = jeu->grille[arriver->colonne][arriver->ligne + 1].piece;
            if (piecePrise) {
                piecePrise->casePiece->piece = NULL;
            }
            jeu->noir->pieces = g_list_remove(jeu->noir->pieces, piecePrise);
        } else {
            piecePrise = jeu->grille[arriver->colonne][arriver->ligne - 1].piece;
            if (piecePrise) {
                piecePrise->casePiece->piece = NULL;
            }
            jeu->blanc->pieces = g_list_remove(jeu->blanc->pieces, piecePrise);
        }

        printf("Vous avez effectuer une prise en passant \n");
    }

    return piecePrise;
}

Piece* effectuerDeplacement(Jeu *jeu, Case *depart, Case *arriver)
{
    Piece *piecePrise = NULL;
    piecePrise = arriver->piece;

    if (arriver->piece) {
        if (jeu->tour == 0) {
            jeu->noir->pieces = g_list_remove(jeu->noir->pieces, arriver->piece);
        } else {
            jeu->blanc->pieces = g_list_remove(jeu->blanc->pieces, arriver->piece);
        }
        g_hash_table_remove_all(jeu->historique);
    }

    if (depart->piece->type == 'P') {
        g_hash_table_remove_all(jeu->historique);
    }

    piecePrise = effectuerPriseEnPassant(jeu, arriver, piecePrise);

    depart->piece->casePiece = arriver;
    arriver->piece = depart->piece;
    depart->piece = NULL;

    return piecePrise;
}

GList* checkEchecPosition(Jeu *jeu, GList* iterateur, GList* position, Case* depart, Piece* pieceDeplacer)
{
    Position* pos = (Position*)iterateur->data;
    Case* arriver = &jeu->grille[pos->colonne][pos->ligne];
    Piece *piecePrise = effectuerDeplacement(jeu, depart, arriver);

    if (isEchec(jeu, jeu->tour)) {
        position = g_list_delete_link(position, iterateur);
    }

    depart->piece = pieceDeplacer;
    pieceDeplacer->casePiece = depart;
    arriver->piece = NULL;

    if (piecePrise) {
        if (jeu->tour == 0)
        {
            jeu->noir->pieces = g_list_append(jeu->noir->pieces, piecePrise);
        } else {
            jeu->blanc->pieces = g_list_append(jeu->blanc->pieces, piecePrise);
        }
        piecePrise->casePiece->piece = piecePrise;
    }
    return position;
}

GList* checkEchec (Case* depart, GList *position, Jeu *jeu)
{
    GList *iterateur = position;
    GList *next = NULL;
    Piece* pieceDeplacer = depart->piece;


    while(iterateur)
    {
        next = iterateur->next;
        position = checkEchecPosition(jeu, iterateur, position, depart, pieceDeplacer);

        iterateur = next;
    }

    return position;
}