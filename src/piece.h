/**
* @copyright
* @file piece.h
* @author Boutes Paul, Cassan Damien
* @brief Definit toutes fonctions relative au deplacements des pieces
*/

#ifndef PIECE
#define PIECE

#include "./structure.h"

/**
* @brief Genere tout les positions que peut atteindre une pieces
* @details Ne prend pas en compte les autres pieces
*
* @param depart Position de depart
* @param jeu Représente l'état du jeu
*
* @return Une liste des positions possibles
*/
GList* genererPosition(Case *depart, Jeu *jeu);

/**
* @brief Genere une liste des coups que peut effectuer une piéce
* @param jeu Le jeu en cours
* @param position Liste des coups possibles a completer avec celle de la piece
* @param depart Position de depart de la piece
* @return Nouvelle liste contenant position plus les coups de la piece
*/
GList* genererPositionPiece(Case *depart, Jeu *jeu, GList *position);

/**
* @brief Genere toutes les positions que peut atteindre un pion
* @details Genere l'avancement de deux case et les prises
* @param depart Position du pion
* @param jeu Represente le jeu actuel
*
* @return Une liste des positions possibles
*/

GList* genererPositionPion(Case *depart, Jeu *jeu);

/**
* @brief Genere toutes les positions que peut atteindre une tour
* @details Genere l'avancement sur toute la ligne et la colonne
*
* @param depart Position de la tour
* @param jeu Etat du jeu actuel
*
* @return Une liste des positions possibles
*/

GList* genererPositionTour(Case *depart, Jeu *jeu);

/**
* @brief Verifie si une case est bien dans l'echequier à partir de sa position
* @details Verifie que les lignes et les colonnes soit compris entre 0 et 7
* @param colonne Indice representant la colonne de la case
* @param ligne Indice representant la ligne de la case
* @return Si la position est valide
*/
gboolean isValid(int colonne, int ligne);


/**
* @brief Génère toutes les positions que peut atteindre un fou
* @details Genere l'avancement sur toutes les diagonales
*
* @param jeu Represente le jeu actuel
* @param depart Position du fou
*
* @return Une liste des positions possibles
*/

GList* genererPositionFou(Case *depart, Jeu *jeu);


/**
*   @brief Genere les positions que peux prendre le fou vers le bas
*   @param depart Position de depart du fou
*   @param jeu Jeu en cours
*   @param position Liste des coups possibles
*   @param direction 1 pour la gauche, -1 pour la droite
*   @return Liste des position completer avec celle du fou
*/
GList* genererPositionFouBas(Case *depart, Jeu *jeu, GList *position, int direction);

/**
*   @brief Genere les positions que peux prendre le fou vers le haut
*   @param depart Position de depart du fou
*   @param jeu Jeu en cours
*   @param position Liste des coups possibles
*   @param direction 1 pour la gauche, -1 pour la droite
*   @return Liste des position completer avec celle du fou
*/
GList* genererPositionFouHaut(Case *depart, Jeu *jeu, GList *position, int direction);
/**
* @brief Génère toutes les positions que peut atteindre le Roi
* @details Genere les positions possibles du Roi autour de lui
*
* @param depart Position du roi
* @param jeu Jeu en cours
*
* @return Une liste des positions possibles
*/

GList* genererPositionRoi(Case *depart, Jeu *jeu);

/**
* @brief Génère toutes les positions que peut atteindre le cavalier
* @details Genere les positions possibles du cavalier autour de lui
*
* @param depart Position du cavalier
*
* @return Une liste des positions possibles
*/

GList* genererPositionCavalier(Case *depart);




/**
* @brief Permet d'ajouter une position possible à une liste
* @details Ajoute une position possible d'une pièce à la liste des positions
*
* @param ligne représente la ligne de la position à ajouter
* @param colonne représente la colonne de la position à ajouter
* @param list représente la liste des positions des pièces
*
* @return Une liste avec une position ajouté
*/

GList* addPosition(int ligne, int colonne, GList *list);




/**
* @brief Verifie qu'un pion puisse effectuer un double pas et active la prise en passant
* @param position Liste des coups possible
* @param depart Position de depart de la piéce
* @param jeu Jeu en cours
*/
GList* verifierPriseEnPassant(GList *position, Case *depart, Jeu *jeu);

/**
* @brief Genere les coups de base du pion
* @details Genere la prise sur les coté et le deplacement tout droit
* @param depart Position de depart de la piece
* @param jeu Jeu en cours
* @param direction Peut prendre 1 ou -1  suivant le joueur effectuent le mouvemennt
* @param position Liste de coups possible
*/
GList* genererPositionPionBase(Case *depart, Jeu *jeu, int direction, GList *position);

/**
* @brief Genere les mouvements d'une tour sur une ligne
* @param jeu Jeu en cours
* @param depart Position de depart de la tour
* @param position Liste des coups possible
*/
GList* genererPositionTourVertical(Jeu* jeu, Case* depart, GList *position);

/**
* @brief Genere les mouvements d'une tour sur une colonne
* @param jeu Jeu en cours
* @param depart Position de depart de la tour
* @param position Liste des coups possible
*/
GList* genererPositionTourHorizontal(Jeu* jeu, Case* depart, GList *position);

#endif