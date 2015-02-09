/**
 * @copyright 
 * @file structure.h
 * @author Boutes Paul, Cassan Damien
 * @brief Definit toutes les structures nessécaire au programme 
 */

#ifndef STRUCTURE
#define STRUCTURE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gstdio.h>


typedef struct Jeu Jeu;

typedef struct Joueur Joueur;

typedef struct Case Case;

typedef Case** Grille;

typedef struct Piece Piece;

typedef struct Fichier Fichier;

typedef struct Option Option;

typedef struct Ia Ia;

typedef struct IaLevel IaLevel;

typedef struct Help Help;

typedef struct Move Move;

typedef struct Position Position;

typedef struct Deplacement Deplacement;

typedef struct ThreadArguments ThreadArguments;


/**
 * @brief Represente un joueur, seul 2 instances seront presentes
 * @details Contient la liste des pieces et toutes le informations relative aux joueur
 * 
 */
struct Joueur {
        /**< Identifiant du joueur : 0 pour le joueur blanc, 1 pour le joueur noir */
        char id;
        /**< Toutes les pieces présente sur l'échequier et appartenent a ce joueur */
        GList *pieces;
        /**< Permet d'acceder rapidement au roi */
        Piece *roi;
};


struct Deplacement {
        /**< Case de depart de la piéce */
        Case *depart;
        /**< Case d'arrivé de la piéce */
        Case *arriver;
};

/**
 * @brief Represente un jeu d'echecs en entier 
 * @details Contient les joueurs, la grille et toutes la configuration du jeu
 * 
 */
struct Jeu {
        /**< Pointeur vers le joueur blanc*/
        Joueur *blanc;
        /**< Pointeur vers le joueur noir */
        Joueur *noir;
        /**< Indique l'id du joueur qui doit jouer ex : 0 pour le joueur blanc*/
        char tour;
        /**< Indique si une prise en passant est possible */
        char prise;
        /**< Indique la colone de la prise en passant*/
        char positionPriseCol;
        /**< Indique la ligne de la prise en passant*/
        char positionPriseLigne;
        /**< Represente la grille utilisé pour ce jeu */
        Grille grille;
        /**< Definit si il est possible d'effectuer un roque avec la tour de gauche pour le joueur noir */
        char positionInitialeTour1Noir;
        /**< Definit si il est possible d'effectuer un roque avec la tour de gauche pour le joueur blanc */
        char  positionInitialeTour1Blanc;
        /**< Definit si il est possible d'effectuer un roque avec la tour de droite pour le joueur noir */
        char positionInitialeTour2Noir;
        /**< Definit si il est possible d'effectuer un roque avec la tour de droite pour le joueur blanc*/
        char  positionInitialeTour2Blanc;
        /**< Historique des coups joué pour la regle des 3 coups */
        GHashTable *historique;

};


/**
 * @brief Represente un position sur l'échequier
 * @details Les 2 attributs peuvent prendre des valeurs comprise entre 1 et 8
 * 
 */
struct Position {
        /**< Indique la ligne avec une valeur comprise entre 1 et 8 */
        int ligne;
        /**< Indique la colonne avec une valeur comprise entre 1 et 8 */
        int colonne;
};



/**
 * @brief Structure Move contenant les paramètres de déplacement
 * @param param1 Premier paramètre de déplacement, case de départ
 * @param param2 Second paramètre de déplacement, case d'arrivé
 * @param code Code de la pièce pour utiliser les déplacements algébrique
 *
 */

struct Move {
        /**< Position de la case de depart */
        GString *param1;
        /**< Position de la case d'arrivé */
        GString *param2;
        /**< Type de la piece a deplacer */
        char code;
        /**< Si un deplacement a été demandé */
        gboolean isOption;
        /**< Si un deplacement algebrique a été demandé */
        gboolean isAlgebrique;
        /**< Si un deplacement est un roque (0 non, 1 petit roque, 2 grand roque)*/
        int isRoque;
};


/**
 * @brief Represente une case de l'échequier 
 * @details Une case de l'echequier contenant la position de la case et le piece dessus
 */
struct Case {
        /**< Indique la colonne avec une valeur comprise entre 1 et 8  */
        int colonne;
        /**< Indique la ligne avec une valeur comprise entre 1 et 8 */
        int ligne;
        /**< Represente la piece presente sur cette case */
        Piece *piece;
};

/**
 * @brief Represente une piece de l'echequier
 * @details Une piece associe a une case, un joueur et definit par un type
 */

struct Piece {
        /**< Initiale du type de la piece ex : R : Roi, F : fou */
        char type;
        /**< Case sur laquelle est positionné la pièce */
        Case *casePiece;
        /**< Joueur auquel appartient la piece */
        Joueur *joueur;
};



/**
 * @brief Structure contenant le nom d'un fichier
 * @param file nom du fichier
 */

struct Fichier {
        /**< Nom du fichier */
        GString *file;
        /**< Definit si un fichier doit etre ouvert */
        gboolean isOption;
};




/**
 * @brief Structure IaLevel contenant le niveau de l'ia
 * @param param Niveau de l'ia, compris entre 1 et 3
 *
 */

struct IaLevel {
        /**< Niveau de l'IA*/
        char param;
        /**< Si un niveau d'IA a été définit */
        gboolean isOption;
};





/**
 * @brief Structure Ia contenant le joueur géré par l'ia
 * @param param entier représentant un joueur, soit 1 soit 2
 *
 */

struct Ia {
        /**< Si un des joueurs est une IA */
        int param;
        /**< Si un des joueurs est une IA */
        gboolean isOption;
};





/**
 * @brief Structure Help permettant de vérifier si l'option '-h' ou '--help' est présente
 * @param help gbooleaneen qui représente si l'aide est présente, false l'aide ne s'affiche pas, sinon elle s'affiche
 *
 */

struct Help {
        /**< Si l'aide est demandé */
        gboolean isOption;
};







/**
 * @brief Structure Value contenant les structures permettant de gérer les lignes de commandes avec leurs paramètres
 * @param index Entier représentant le nombre d'option qui sont ensuite mis dans tab à la position index
 * @param tab Tableau d'entier qui permet de recenser les options entrées
 * @param help Structure permetttant de gérer l'option '-h' et '--help'
 * @param load Structure permettant de gérer l'option '-l'
 * @param save Structure permettant de gérer l'option '-s'
 * @param base Structure permettant de gérer l'option '-d'
 * @param piece Structure permettant de gérer l'option '-p'
 * @param algeb Structure permettant de gérer l'option '-a'
 * @param level1 Structure permettant de gérer l'option '-l1'
 * @param level2 Structure permettant de gérer l'option '-l2'
 * @param ia1 Structure permettant de gérer l'option '-c1'
 * @param ia2 Structure permettant de gérer l'option '-c2'
 *
 */

struct Option {
        /**< Option d'aide */
        Help help;
        /**< Fichier a charger */
        Fichier load;
        /**< Fichier a sauvegarder */
        Fichier save;
        /**< Base d'ouverture a utiliser */
        Fichier base;
        /**< Deplacment effectuer */
        Move piece;
        /**< Niveau de l'IA pour le joueur 1 */
        IaLevel level1;
        /**< Niveau de l'IA pour le joueur 2 */
        IaLevel level2;
        /**< Définit le joueur comme une IA */
        Ia ia1;
        /**< Définit le joueur comme une IA  */
        Ia ia2;
};


struct ThreadArguments {

        Jeu *jeu;

        int *count_thread;

        int *score;

        Deplacement **bestMove;

        Deplacement *move;

        GString *neural_network_file;

};

#endif
