/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien, DRUELLE Mathias
 * @brief Header contenant les prototypes des fonctions du fichier hash.c
 */

#ifndef HASH
#define HASH


#include "./structure.h"

    /**
     * @brief Permet de convertir une pièce du jeu en hash
     *
     * @param data pointeur vers la pièce à convertir
     * @param userData pointeur vers le hash qui va être modifié
     */

    void pieceToHash(gpointer data, gpointer userData);


    /**
     * @brief Permet de creer un hash à partir d'une liste de pièces
     * 
     * @param pieces liste de pièces
     * @return un nouveau hash
     */
    GString* createHash(GList *pieces);



#endif