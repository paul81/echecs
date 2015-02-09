/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien
 * @brief Header contenant les prototypes des fonctions dans le fichier option.c
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "./fichier.h"
#include "./deplacement.h"
#include "./structure.h"


/**
 * @brief Permet de récupérer les options et arguments
 * @details Permet de récupérer les options et les arguments passés en ligne de commande, et met à jour les
 * structures permettant de gérer les lignes de commandes en fonction de l'option
 *
 * @param argc Entier représentant le nombre d'option
 * @param argv Tableau contenant les différentes options entré en ligne de commande
 *
 * @return retourne 0 si tout va bien à la fin de l'éxécution
 */

Option command(int argc, char **argv);



/**
 * @brief Initialise la structure data
 * @details Permet d'initialiser la structure data qui gère les options, et initialise donc les sous-structures,
 * 0 pour des entiers
 * "" pour des chaînes
 * '\0' pour des caractères
 *
 * @param data Structure contenant les structures qui permettent la gestion des options qui doit être initialisé
 */

void initialize(Option *data);



/**
 * @brief Libere la memoire alloué durant l'execution du programme
 * @details Libere toutes la memoires alloué lors de l'initialisation
 *
 * @param jeu Le jeu dont la memoire doit etre liberé
 * @param data Les options passé a l'executable
 */
void freeValue(Jeu *jeu, Option *data);




/**
 * @brief Met le niveau de l'ia
 * @details Permet de mettre le niveau de l'ia, entre 1 et 3, pour le joueur 1 et 2 en fonction du parametre n
 *
 * @param level Niveau de l'ia compris entre 1 et 3
 * @param n si n = 1, c'est le joueur1, sinon c'est le joueur 2
 */

int setIaLevel(IaLevel *level, int n);

/**
 * @brief Défini quel joueur est géré par l'ordinateur
 * @details Soit le joueur 1 est géré par ordinateur, soit le 2, soit les deux
 *
 * @param player Joueur qui est géré par ordinateur
 */

void setIaPlayer(Ia *player);

/**
 * @brief Libere la memoire alloué par une piece
 * @details Fonction utilisé par le foreach sur la liste des pieces
 *
 * @param data La piece pour laquelle if faut liberer la mémoire
 */

void freeElement(gpointer data);

/**
* @brief Copie une position contenue danns une chaine dans une variable de type Move
* @details prend une chaine decrivant un mouvement sout la forme algebrique et la transforme en un Move
*
* @param data Les options passé au programme
* @param algebrique definie si la position est en notation algebrique
*/

void copyPosition(Option *data, gboolean algebrique);

/**
* @brief Libere la memoire alloué pour le stockage des options
* @param data les options passé en arguments
*/
void freeOption(Option *data);

/**
* @brief Libere la memoire alloué la grille et les joueur
* @param jeu Le jeu à libéré
*/
void freeJeu(Jeu *jeu);

/**
* @brief Interprete un deplacement en notation algebrque et le convertit en mouvement
* @param taille Longueur de la chaine contenant le deplacement en notation algebrique
* @param token chaine contenant le deplacement
* @param data Aguments passé au programme
*/
void copyPositionAlgebrique (int taille, char* token, Option *data);

/**
* @brief Verifie si un deplacement est un roque
* @param taille Longueur de token
* @param token La commande en notation algbrique
* @param data Les options passé au programme
*/
void isRoqueAlgebrique(int taille, char* token, Option *data);

/**
* @brief Transforme un nombre entre 1 et 8 en un autre nombre (1 -> 8) (2 ->7) (3->6) ect
* @param position Position de depart
* @return la valeur transformer (1 -> 8) (2 -> 7)
*/
int transformPosition (int position);

#endif
