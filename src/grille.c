/**
 * @copyright
 * @file grille.c
 * @author 
 * @brief 
 * @details 
 */

#include "./grille.h"


void createGrille(Jeu *jeu) {
    int i;
    int j;
    int nbCol = 8;
    jeu->grille = malloc(8 * sizeof(Case));
    for (i = 0; i < nbCol; i++) {
      jeu->grille[i] = malloc(8 * sizeof(Case));
      for (j = 0; j < nbCol; j++) {
            jeu->grille[i][j].piece = NULL;
            jeu->grille[i][j].ligne = j;
            jeu->grille[i][j].colonne = i;
      }
    }
}


void addPiece(Jeu *jeu, Joueur *joueur, GString *hash, char type, int position) {
    Piece *piece = malloc(sizeof(Piece));
    int colonne = hash->str[position+1] - 'a';
    int ligne = hash->str[position+2] - '1';
    piece->type = type;
    piece->casePiece = &jeu->grille[colonne][ligne];
    piece->joueur = joueur;
    joueur->pieces = g_list_append(joueur->pieces, piece);
    jeu->grille[colonne][ligne].piece = piece;

    if(type == 'R') {
        joueur->roi = piece;
    }
}


void addPieceFromHash (GString *hash, Jeu *jeu, Joueur* joueur, int i)
{
    switch (hash->str[i]) {
        case 'T':
            addPiece(jeu, joueur, hash, 'T', i);
            break;
        case 'F':
            addPiece(jeu, joueur, hash, 'F', i);
            break;
        case 'C':
            addPiece(jeu, joueur, hash, 'C', i);
            break;
        case 'R':
            addPiece(jeu, joueur, hash, 'R', i);
            break;
        case 'D':
            addPiece(jeu, joueur, hash, 'D', i);
            break;
        case 'P':
            addPiece(jeu, joueur, hash, 'P', i);
            break;
        default:
            /* On est pas sur une piece mais sur la position*/
            break;
    }
}



void initializeGrille(Jeu *jeu, Joueur *joueur, GString *hash) {
    int i;
    for (i = 0; i < (int) hash->len; ++i) {
        addPieceFromHash(hash, jeu, joueur, i);
    }
}




void initializeJeu(Jeu *jeu) {
    jeu->blanc = malloc(sizeof(Joueur));
    jeu->noir = malloc(sizeof(Joueur));
    initializeJoueur(jeu->blanc);
    initializeJoueur(jeu->noir);
    jeu->blanc->id = 0;
    jeu->noir->id = 1;
    createGrille(jeu);
    jeu->tour = 0;
}



void initializeJoueur(Joueur *joueur) {
    joueur->pieces = NULL;
    joueur->roi = NULL;
}



