/**
* @copyright
* @file cef_base.h
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions relative a la gestion de la memoire de chromium
*/
#ifndef CEF_BASE
#define CEF_BASE

#include <include/capi/cef_base_capi.h>

/**
* @brief Compte une nouvelle reference vers self
* @param self Objet auquel ajouté la reference
* @return Le nombre de reference vers cette objet
*/
int addRef(cef_base_t *self) ;

/**
* @brief Libere la memoire alloué par un object de CEF lorsqu'il ny a plus de reference
* @param self Objet a supprimer
* @return Code d'erreur
*/
int release(cef_base_t* self);

/**
* @brief Renvoie le nombre de reference vers l'objet self
* @param self Objet a regarder
* @return Nombre de references restantes
*/
int getRefct(cef_base_t *self);

/**
* @brief Initialise unn objet et commence a compter les reference de celui-ci
* @param base Objet a initialiser
*/
void initializeCefBase(cef_base_t *base) ;

#endif