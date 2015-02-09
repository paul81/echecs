/**
* @copyright
* @file ia.h
* @author Boutes Paul, Cassan Damien
* @brief Definitions de toutes fonctions relative a l'intelligence artificielle
*/

#ifndef IA
#define IA

#include <time.h>
#include "jeu.h"
#include <floatfann.h>

/**
* @brief Transforme une listes positions en un deplacement (pointeur vers la grille)
* @param depart Case de depart de la piece effectuant les deplacement
* @param positions listes des positions d'arriver
* @param jeu Le jeu dans lequelle se déroule les deplacements
*/
GList* positionToDeplacement(Case *depart, GList* positions, Jeu *jeu);

/**
* @brief Utilise l'alogithme du negamax pour trouver le meilleur coups
* @param jeu Le jeu qui doit étre évalué
* @param profondeur Nombre de repetition du négamax
* @param joueur 1 si c'est le tour du joueur blanc ou -1 sinon
* @param alpha parametre alpha du minimax
* @param beta parametre beta du minimax
* @param neural_network Les matrices necessaire à l'utilisation du réseau de neuronne
*/
int negamaxAlpha(Jeu *jeu, int profondeur, int joueur, int alpha, int beta, struct fann *neural_network);

/**
* @brief Partie principale du negamax, parcours toutes les deplacements et evalue ou relance negamax
* @param deplacements Liste des deplacements possible
* @param score Le score actuelle
* @param max le score maximal
* @param alpha le parametre alpha du negamax
* @param beta le parametre beta du negamax
* @param jeu le jeu sur lequelle effectuer le negamax
* @param profondeur du negamax
*/
int parcoursNegamax (GList *deplacements, int score, int max, int alpha, int beta, Jeu *jeu, int profondeur,
        int joueur, struct fann *neural_network);

/**
* @brief Genere toutes les deplacements que peut effectuer un joueur
* @param jeu Le jeu dans lequelle se déroule les deplacements
*/
GList* genererToutesLesPositions(Jeu *jeu);


/**
* @brief Permet d'annuler un deplacement (y compris une prise)
* @param depart Case de depart de la piece
* @param arriver Case d'arriver de la piece
* @param jeu Le jeu dans lequelle se déroule les deplacements
* @param piecePrise La piece qui a été prise durant le deplacement si il y en a une
* @param pieceDeplacer La piece qui a été deplacé
*/

void annulerDeplacement(Case *depart, Case *arriver, Jeu * jeu, Piece *piecePrise, Piece *pieceDeplacer);


/**
* @brief Cette fonction evalue le jeu grace au réseau de neurones
* @param jeu Le jeu dans lequelle se déroule les deplacements
* @param neural_network Le réseau de neurones déjà initialiser
*/
int evaluerJeu(Jeu *jeu, struct fann *neural_network);

/**
* @brief Change le tour du jeu
* @param jeu Le jeu pour lequelle changé le tour
*/
void changerTour (Jeu *jeu);

/**
*  @brief Joue un tour en utilisant l'IA
*  @param jeu Le jeu pour lequelle joué
*  @param option Les options de la partie
*/
int playIA (Jeu *jeu, Option *option);

/**
* @brief Fonction lancé dans un thread qui lance un négamax
* @param data ThreadArguments passé au thread
*/
void ia_thread(gpointer data);

/**
* @brief Permet de copier un jeux y compris les element pointés
* @param original Le jeu original a copier
* @param copy Le jeux sur lequelle copier
*/
void copierJeux(Jeu *original, Jeu *copy);

/**
* @brief Parcours toutes les pieces et leur attribue une valeur numerique et renvoie la somme
* @param Le jeu sur lequelle sont les pieces
*/
int evaluerToutesLesPieces(Jeu *jeu);

/**
* @brief Evalue une piece
* @param piece La piece a evaluer
*/
int evaluerPiece (char piece);

/**
* @brief Permet de convertir un type de piece en une valeur numerque
* @param piece le type de la piece
*/
int convertPieceToVal (char piece);

/**
* @brief Charge le réseau de neurones depuis un fichier
* @param option Les options passé au jeux
*/
GString *loadNeuralNetwork(Option *option);

/**
* @brief Initialise n copie du jeux
* @param nb_coups Le nombre de copies a creer
* @param jeu Le jeu initiale a copier
**/
Jeu* initialiserNJeux(int nb_coups, Jeu *jeu);

/**
* @brief Joue un tour avec l'IA
* @param nb_coups Nombre de coups que peux realiser le joueur
* @param copyJeu nb_coups copie du jeu
* @param bestMove Le meilleur deplacement à modifier dans la fonction
* @param count_thread Le nombre de thread ayant terminer
* @param score Le score du meilleur coups
* @param neural_network_file Le nom du fichier contenant le reseau de neurones
* @param positions Les deplacements possible a effectuer
*/
void lancerIA(int nb_coups, Jeu* copyJeu, Deplacement** bestMove, int *count_thread, int *score, GString *neural_network_file, GList *positions);

#endif