/**
 * @copyright 
 * @file fichier.h
 * @author Boutes Paul, Cassan Damien
 * @brief Contient les fonctions permettant de gérer les fichiers 
 */

#ifndef FICHIER
#define FICHIER

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "./structure.h"
#include "./hash.h"


/**
* @brief Lit les clé et valeur du file descriptor pour le remettre dans la table de hachage
* @details Permet de mettre la table de hachage à jour, on retrouve un état de l'échiquier
*
* @param fd file descriptor dans lequel on lit le hash
* @param table Table de hachage contenant l'état du jeu
*/
void readHashTable(int fd, GHashTable *table);


/**
* @brief Ecrit la clé et la valeur de la table de hachage dans le file descriptor
* @details La forme du Hash est : "NombreDeCle tailleDuHash Hash Valeur"
*
* @param fd file descriptor dans lequel on écrit le hash
* @param table Table de hachage contenant l'état du jeu
*/
void writeHashTable(int fd, GHashTable *table);



/**
 * @brief Ecrit le hash dans le file descriptor
 * @details Ecrit le hash sous la forme "tailleDuHash Hash"
 *
 * @param fd file descriptor dans lequel on écrit le hash
 * @param hash Chaine de caractère qui représente un hash
 */
void writeHash(int fd, GString *hash);


/**
 * @brief Charge un fichier
 * @details Permet de charger un fichier entrée en ligne de commande
 *
 * @param file Nom du fichier à chargé
 * @param jeu Represente le jeu actuel
 * @param ghash1 Hash du joueur 1
 * @param ghash2 Hash du joueur 2
 */

int load(GString *file, Jeu *jeu, GString *ghash1, GString *ghash2);


/**
 * @brief Sauvegarde la partie dans un fichier
 * @details Permet de sauvegarder l'état de la partie dans un fichier entrée en ligne de commande
 *
 * @param file Nom du fichier sauvegardé
 * @param jeu Represente le jeu actuel
 */

void save(GString *file, Jeu *jeu);


/**
 * @brief Charge la base de donnée d'ouverture
 * @details Permet de charger une base de donnée d'ouverture qui contient de multiples ouvertures
 *
 * @param file Nom de la base d'ouverture à chargé
 */

void base(GString *file);


/**
*   @brief Lis un hash dans un fichier representer par sa taille puis le hash
*   @param fd File decscriptor representant le fichier
*   @param ghash Une GString contenant le hash (valeur de retour)
*/
void readHash(int fd, GString* ghash);


#endif
