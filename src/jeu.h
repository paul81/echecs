/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien
 * @brief header contenant les entêtes des fonctions du fichier jeu
 */

#ifndef JEU
#define JEU

#include <stdio.h>
#include <stdlib.h>
#include "./option.h"
#include "./grille.h"
#include "./hash.h"
#include "./structure.h"
#include "./ia.h"



/**
 * @brief Initialise le jeu
 * @details Gère les options et les arguments via les structures qui leurs sont associé, et lance les actions correspondante
 * en fonction de l'option
 * @param jeu
 * @param option Structure contenant toutes les structures qui permettent la gestion des options
 * @return retourne 0 à la fin de l'éxécution
 */


int initialiser(Jeu *jeu, Option *option);

/**
* @brief Fonction principale permettant de verifier et effectuer un mouvement
* @details Verifie que les parametres soit correcte et lance la fonction deplace
* @param jeu Le jeu sur lequelle effectuer le deplacement
* @param option Les options passé en ligne de commande
*/

int jouer(Jeu *jeu, Option *option);

/**
* @brief Affiche l'aide du jeu
*/
int displayHelp(void);

/**
* @brief Place les pieces sur l'echequier et initialise le jeu
* @details Genere les listes de pieces et initialise les attributs de jeu
* @param jeu Le jeu a initialiser
* @param hash1 Un hash representant les pieces du joueur 1
* @param hash2 Un hash representant les pieces du joueur 2
*/

void setNewGame(Jeu *jeu, GString *hash1, GString *hash2);

/**
* @brief Initialise un plateau de jeu grace au option passé en arguments
* @details Verifie les arguments et appele les fonctions reponsables de l'initialisation du jeu
* @param jeu Le jeu a initialiser
* @param option Les option passé en ligne de commande
* @param hash Un hash contenant les piéces du joueur 1
* @param hash2 Un hash contenant les piéces du joueur 2
*/

int setOption(Option *option, Jeu *jeu, GString *hash, GString *hash2);

/**
* @brief Effectue un deplacement a partir de la notation algebrique
* @param jeu Jen en cours
* @param option Arguments passé au programme
* @param arrive Case d'arrivé de la piece
*/

int deplacementAlgebrique(Jeu *jeu, Option *option, Case* arrive);

/**
* @brief Transforme une piece en une autre piece choisie par l'utilisateur
* @param piece la piece a transformer
* @return 0 si le changement c'est bien passez
*/
int changerPiecePromotion(Piece *piece);

/**
* @brief Effectue une promotion
* @param jeu Le jeu en cours
* @param retour Le code d'erreur de la fonction deplacer
* @return Un nouveau code d'erreur
*/
int effectuerPromotion (Jeu *jeu, int retour);

/**
* @brief Si un roque a ete demander remplace le deplacement par un roque
* @param jeu Jeu en cours
* @param option Les arguments passé au programme
*/
void roqueDepuisNotationAlgebrique (Jeu *jeu, Option *option);

#endif