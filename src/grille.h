/**
 * @copyright
 * @file grille.h
 * @author Boutes Paul, Cassan Damien
 * @brief Contient toutes les signature des fonctions relative aux grilles
 */

#ifndef GRILLE
#define GRILLE

#include <stdio.h>
#include <stdlib.h>
#include "./structure.h"




/**
 * @brief Initialise un jeu (Grille, joueur, pieces)
 * @details Permet d'allouer la memoires necessaire a un jeu d'echecs
 *
 * @param jeu Le jeu a initialiser
 */

void initializeJeu(Jeu *jeu);

/**
 * @brief Initialise un joueur
 * @details Permet d'allouer la memoires necessaire a un joueur et initialise ses attributs
 *
 * @param joueur Le joueur a initialiser
 */

void initializeJoueur(Joueur *joueur);

/**
 * @brief Alloue la memoire pour un grille de jeu
 * @details Permet d'allouer la memoires necessaire a une grille
 *
 * @param jeu Le jeu a initialiser
 */

void createGrille(Jeu *jeu);

/**
 * @brief Creer une liste de pieces a partir d'un hash et remplie la grille
 * @details Parcours le hash et creer la liste des pieces puis a partir de la liste initialise la grille
 *
 * @param jeu Le jeu contenant la grille
 * @param joueur Le joueur auquel appartient le hash
 * @param hash le hash contenant les pieces du joueurs et leur positions
 */

void initializeGrille(Jeu *jeu, Joueur *joueur, GString *hash);

/**
 * @brief Ajoute une piece a la liste des pieces d'un joueur
 * @details Complete la liste des pieces d'un joueurs avec la piece donnée 
 *
 * @param jeu Le jeu contenant la grille
 * @param joueur Le joueur auquel appartient la piece
 * @param hash Le hash contenant les pieces du joueurs et leur positions
 * @param type Le type de la piece
 * @param position La position du curseur dans le hash
 */

void addPiece(Jeu *jeu, Joueur *joueur, GString *hash, char type, int position);

/**
*   @brief Ajoute une piece a un joueur a partir d'un hash
*   @param hash Le hash a interpreter
*   @param jeu Le jeu en cours
*   @param joueur Le joueur auquelle doit appertenir la piéce
*   @param i la position du curseur dans le hash
*/
void addPieceFromHash (GString *hash, Jeu *jeu, Joueur* joueur, int i);



#endif
