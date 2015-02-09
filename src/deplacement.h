/**
 * @copyright 
 * @file deplacement.h
 * @author Boutes Paul, Cassan Damien
 * @brief Contient les signature de fonctions permettant de gérer les déplacements des pions dans le jeu 
 */

#ifndef DEPLACEMENT
#define DEPLACEMENT

#include <stdio.h>
#include <stdlib.h>
#include "./structure.h"
#include "./option.h"
#include "./piece.h"


/**
* @brief Met à jour la table de hachage contenant l'historique des états du jeu
* @details Les clés sont des hash, et les valeurs des entiers
* @param jeu Représente le jeu dans son état actuel
* @param retour Valeur de retour
*/
int updateHistorique(Jeu *jeu, int retour);


/**
 * @brief Déplace une pièce sur l'échiquier
 * @details Permet de déplacer une pièce d'une case à une autre, via la ligne de commande
 * @param depart Case de depart de la piece
 * @param arrive Case d'arriver de la piece
 * @param jeu Represente le jeu actuel
 */

int deplace(Case *depart, Case *arrive, Jeu *jeu);

/**
 * @brief Déplace une pièce sur l'échiquier selon la notation algébrique
 * @details Permet de déplacer une pièce selon la notation algébrique, si c'est un pion, la parametre pion vaut true et
 * l'on n'ajoute pas de code pour la pièce, sinon on ajoute devant le déplacement le code de la pièce (R,T,F,C)
 *
 * @param piece Pièce qui est déplacé
 * @param pion Vérifie si l'on déplace un pion
 */

void algebrique(Move *piece, gboolean pion);



/**
* @brief Change une piece de position est effectue une prise si il ya une autre piece
* @details Definit la case de depart de la piece comme n'ayant plus de piece et fait pointer l'attribut piece de la
* case d'arrivée vers la piece. Verifie si une prise en passant est possible
* @param jeu Un pointeur vers le jeu en cours
* @param depart Case de depart de la piéce
* @param arriver Case ou doit arriver la piéce
*/
Piece* effectuerDeplacement(Jeu *jeu, Case *depart, Case *arriver);

/**
* @brief Pour chaque deplacement d'une piece, elimine ceux qui mettent le roi en echec
* @details Simule le coup et utilise isEchec pour verifier que le mouvement est possible
* @param depart Case de depart de la piece
* @param position Liste des coups possible
* @param jeu Un pointeur vers le jeu en cours
*/
GList* checkEchec (Case* depart, GList *position, Jeu *jeu);

/**
* @brief Verifie si la configuration de l'echequier met le roi en echec
* @details
*
* @param jeu Jeu en cours
* @param iterateur Mouvement a analyser
* @param position Liste de mouvement possible
* @param depart Case de depart de la piece
* @param pieceDeplacer Piece entrain d'etre deplacer
*/
GList* checkEchecPosition(Jeu *jeu, GList* iterateur, GList* position, Case* depart, Piece* pieceDeplacer);

/**
*  @brief Verifie si un joueur est en echec
*  @details Simule tout les deplacements possible du joueur adverse et verifie que le roi n'est pas dans cette liste
*  @param jeu Un pointeur vers le jeu en cours
*  @param joueur Verifie si ce joueur est en echec
*/
gboolean isEchec(Jeu *jeu, char joueur);

/**
* @brief Récupère la position d'une case
* @details Permet de récupérer la position d'une case, et le converti pour notre utilisation
*
* @param colonne représente la colonne de la case
* @param ligne représente la ligne de la case
* @param jeu représente le jeu dans son état actuel
*
* @return Une case de la grille
*/

Case* getCase(char colonne, char ligne, Jeu *jeu);

/**
* @brief Vérifie les positions de la liste de pièce
* @details Vérifie si les positions sont valides, si elles sont présentes dans la grille
*
* @param position liste de pièce
* @param jeu représente l'état du jeu
*
* @return une liste de pièce contenant des positions d'arrivée valide
*/

GList* check(GList *position, Jeu *jeu);

/**
* @brief Effectue un roque si le joueur a la possibilité de le faire
* @details Echange la position de la tour et du roi, et empeche un autre roque d'etre effectuer
* @param depart Case de depart du roi
* @param arrive Case d'arrivé du roi
* @param jeu Jeu en cours
*/

int effectuerRoque(Case *depart, Case *arrive, Jeu *jeu);

/**
* @brief Verifie qu'il est possible d'effectuer un roque
* @details Utilise les autres fonctions du roques pour tester et effectuer le roque
* @param jeu Jeu en cours
* @param parcours Case intermediaire a coté du roi
* @param arrive Case d'arrivé du roi
* @param depart Case de depart du roi
* @param tour Un pointeur vers la tour effectuant le roque
* @param roi Un pointeur vers le roi effectuant le roque
*/
int verifierRoque(Case *parcours, Case *depart, Case *arrive, Jeu *jeu, Piece *tour, Piece *roi);

/**
* @brief Verifie le deplacement intermediaire du roi
* @details Verifie que le roi n'est pas en echec lors de son roque
* @param parcours Case intermediaire a coté du roi
* @param arrive Position d'arrivé du roi
* @param roi Un pointeur vers le roi
* @param jeu Le jeu en cours
* @param tour Un pointeur vers la tour
* @param depart Case de depart du roi
*/
int verifierRoqueDeplacement(Case* arrive, Piece *roi, Jeu *jeu, Piece *tour, Case *parcours, Case *depart);

/**
* @brief Effectue le mouvement final du roque
* @details Echange la position de la tour et du roi definitivement
* @param jeu Jeu en cours
* @param direction Direction dans laquelle est effectuer le roque
*/
int validerRoque(Jeu *jeu, int direction);

/**
* @brief Verifie et effectue une prise en passant si possible
* @details Si il y a une possibilité d'effectuer une prise en passant
* alors l'effectue et remet a zero le compteur de prise
* @param jeu Jeu en cours
* @param arriver Position d'arrivé du pion effectuant la prise en passant
* @param piecePrise Piece prise par la prise en passant
*/
Piece* effectuerPriseEnPassant(Jeu *jeu, Case* arriver, Piece *piecePrise);

/**
*   @brief Verifie si le joueur blanc est en echec
*   @param jeu Jenn en cours
*   @return Indique si le joueur est en echec
*/
gboolean isEchecBlanc(Jeu *jeu);

/**
*   @brief Verifie si le joueur noir est en echec
*   @param jeu Jeu en cours
*   @return Indique si le joueur est en echec
*/

gboolean isEchecNoir(Jeu *jeu);

/**
*   @brief Verifie si le joueur entrain de jouer et en echec et mat
*   @param jeu Jeu en cours
*   @param positions Liste de coups possible
*   @return Un code d'erreur si il y a echec et mat, 0 sinon
*/

int verifieEchecEtMat(Jeu *jeu, GList* positions);

/**
*   @brief Verifie si le joueur et en pat ou en echec
*   @param jeu Jeu en cours
*   @return 100 pour un echec et mat des blancs, 101 pour les noirs,
*           102 pour un pat des blancs, 103 pour les noirs
*/
int effectuerEchetEtMat(Jeu *jeu);

/**
*   @brief Verifie si un deplacement est possible
*   @param jeu Jeu en cours
*   @param iterateur Liste des coups possible
*   @param arrive Case d'arrivé de la piece
*   @param depart Case de depart de la piece
*   @return Un code d'erreur si le deplacement est impossible, 0 sinon
*/

int verifierDeplacement (Jeu* jeu, GList* iterateur, Case *arrive, Case *depart);

/**
*   @brief Cherche si le deplacement du joueur est compris dans ceux possible
*   @param jeu Jeu en cours
*   @param depart Position de depart de la piece
*   @param arrive Position d'arrivé souhaitait par le joueur
*   @return Un code d'erreur si le deplacement est impossible, 0 sinon
*/
int trouverDeplacement(Jeu *jeu, Case *depart, Case *arrive);

/**
*   @brief Permet d'annuler des possibilité de roque si un roi ou une tour effectue un mouvement
*   @param jeu Jeu en cours
*   @param depart Case de depart de la piece effectuant le mouveme,t
*/

void annulerRoque(Jeu *jeu, Case *depart);

/**
*   @brief Si un pion effectue un double pas active la prise en passant pour le prochain tour
*   @param jeu Jeu en cours
*   @param depart Case de depart du pion
*   @param arrive Case d'arriver du pion
*/

void activerPrisePassant(Jeu *jeu, Case *depart, Case *arrive);

#endif
