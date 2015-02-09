/**
* @copyright
* @file cef_client.h
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions de callback utiliser par chromium
*/



#ifndef CEF_CLIENT
#define CEF_CLIENT

#include "cef_base.h"
#include "include/capi/cef_client_capi.h"





/**
* @brief Retourne le handler charger de l'affichage
*/
struct _cef_display_handler_t* get_display_handler(struct _cef_client_t* self);

/**
* @brief Retourne le handler charger du drag and drop de fichier
*/
struct _cef_drag_handler_t*  get_drag_handler(struct _cef_client_t* self);

/**
* @brief Retourne le handler charger du focus
*/
struct _cef_focus_handler_t*  get_focus_handler(struct _cef_client_t* self);

/**
* @brief Retourne le handler charger des evenements du clavier
*/
struct _cef_keyboard_handler_t*  get_keyboard_handler(struct _cef_client_t* self);

/**
* @brief Retourne le handler charger de la gestion de processus
*/
struct _cef_life_span_handler_t*  get_life_span_handler(struct _cef_client_t* self);

/**
* @brief Retourne le handler charger du status load
*/
struct _cef_load_handler_t*  get_load_handler(struct _cef_client_t* self) ;

/**
* @brief Retourne le handler charger du rendue off-screen
*/
struct _cef_render_handler_t*  get_render_handler(struct _cef_client_t* self) ;

/**
* @brief Retourne le handler charger des requetes
* @details Il permet d'intercepter des requete et de les modifiers
*/
struct _cef_request_handler_t*  get_request_handler(struct _cef_client_t* self) ;

/**
* @brief Retourne le handler qui se charge des dialogues
*/
struct _cef_dialog_handler_t* CEF_CALLBACK get_dialog_handler(struct _cef_client_t* self);

/**
* @brief Recoit et traite les message passé entre les differents processus
*/
int  on_process_message_received(
        struct _cef_client_t* self,
        struct _cef_browser_t* browser, cef_process_id_t source_process,
        struct _cef_process_message_t* message) ;

/**
* @brief Initialise le client handler
* @details Alloue la memoire, ajoute la gestion des reference et associe les handles à celui-ci
*/
void initialize_client_handler(cef_client_t* client) ;

#endif