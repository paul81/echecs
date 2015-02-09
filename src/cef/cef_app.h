/**
* @copyright
* @file cef_app.h
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions permettant de definir les interaction de l'application avec chromium
*/

#ifndef CEF_APP
#define CEF_APP

#include "cef_base.h"
#include <include/capi/cef_app_capi.h>
#include "../jeu.h"


/**
* @brief Permet de rajouter des arguments a la ligne de commande
* @details Provides an opportunity to view and/or modify command-line arguments before
* processing by CEF and Chromium. The |process_type| value will be NULL for
* the browser process. Do not keep a reference to the cef_command_line_t
* object passed to this function. The CefSettings.command_line_args_disabled
* value can be used to start with an NULL command-line object. Any values
* specified in CefSettings that equate to command-line arguments will be set
* before this function is called. Be cautious when using this function to
* modify command-line arguments for non-browser processes as this may result
* in undefined behavior including crashes.
* @param self Le handler
* @param process_type Prend la valeur zygote si c'est un sous processus sous linux
* @param command_line Les arguments passé en ligne de commande
*/
void onBeforeCommandLineProcessing(
        struct _cef_app_t *self, const cef_string_t *process_type,
        struct _cef_command_line_t *command_line);


/**
* @brief Permet de modifier les schema enregistrer
* @param self Permet d'acceder au handler
* @param registrar Le schema enregistrer
*/
void onRegisterCustomSchemes(
        struct _cef_app_t *self,
        struct _cef_scheme_registrar_t *registrar);


/**
* @brief Convertit une chaine de caractere c en UTF16
* @param str La chaine en convertir
* @param cefUrl La chaine convertit
*/
void convert(char *str, cef_string_t* cefUrl) ;


/**
* @brief Fonction appellé depuis javascript, verifiant si une piece est bien sur unen case
* @param self Pointeur vers la fonction
* @param name Nom de la fonctionn
* @param object Lien vers le contexte javascript (V8)
* @param argumentsCount Nombre d'arguments
* @param arguments Arguments passé en javascript
* @param retval Valeur de retour pour le javascript
* @param exception Exception a lancé coté javascript
* @return 1 Si la fonction c'est correctement déroulé
*/
int checkCase (struct _cef_v8handler_t* self,
        const cef_string_t* name,
        struct _cef_v8value_t* object,
        size_t argumentsCount,
        struct _cef_v8value_t* const* arguments,
        struct _cef_v8value_t** retval,
        cef_string_t* exception) ;

/**
* @brief Fonction appellé depuis javascript, Verifie si une promotion a eu lieu et recupere le type de la piece
* @param self Pointeur vers la fonction
* @param name Nom de la fonctionn
* @param object Lien vers le contexte javascript (V8)
* @param argumentsCount Nombre d'arguments
* @param arguments Arguments passé en javascript
* @param retval Valeur de retour pour le javascript
* @param exception Exception a lancé coté javascript
* @return 1 Si la fonction c'est correctement déroulé
*/
int promotion (struct _cef_v8handler_t* self,
        const cef_string_t* name,
        struct _cef_v8value_t* object,
        size_t argumentsCount,
        struct _cef_v8value_t* const* arguments,
        struct _cef_v8value_t** retval,
        cef_string_t* exception);

/**
* @brief Fonction appellé depuis javascript, Effectue un deplacement coté c
* @param self Pointeur vers la fonction
* @param name Nom de la fonctionn
* @param object Lien vers le contexte javascript (V8)
* @param argumentsCount Nombre d'arguments
* @param arguments Arguments passé en javascript
* @param retval Valeur de retour pour le javascript
* @param exception Exception a lancé coté javascript
* @return 1 Si la fonction c'est correctement déroulé
*/
int deplacerPiece(
        struct _cef_v8handler_t *self,
        const cef_string_t *name,
        struct _cef_v8value_t *object,
        size_t argumentsCount,
        struct _cef_v8value_t *const *arguments,
        struct _cef_v8value_t **retval,
        cef_string_t *exception);

/**
* @brief Fonction appellé depuis javascript, Charge un fichier contenant une partie d'echec
* @param self Pointeur vers la fonction
* @param name Nom de la fonctionn
* @param object Lien vers le contexte javascript (V8)
* @param argumentsCount Nombre d'arguments
* @param arguments Arguments passé en javascript
* @param retval Valeur de retour pour le javascript
* @param exception Exception a lancé coté javascript
* @return 1 Si la fonction c'est correctement déroulé
*/
int loadFile (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception);




/**
* @brief Fonction appellé depuis javascript, sauvegarde un fichier contenant une partie d'echec
* @param self Pointeur vers la fonction
* @param name Nom de la fonctionn
* @param object Lien vers le contexte javascript (V8)
* @param argumentsCount Nombre d'arguments
* @param arguments Arguments passé en javascript
* @param retval Valeur de retour pour le javascript
* @param exception Exception a lancé coté javascript
* @return 1 Si la fonction c'est correctement déroulé
*/
int saveFile (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception);

/**
* @brief Genere un tableau javascript contenant les pieces de l'echequier
* @return Un tableau javascript (V8)
*/
cef_v8value_t* genererListePieces(void);


/**
* @brief Fonction appelé par chromium lors de la creation du contexte javascript
* @param self Le handler
* @param browser Un pointeur vers le navigateur
* @param frame Un pointeur vers l'onglet courant
* @param context Le contexte javascript pour cette fenetre
*/
void onContextCreated(
        struct _cef_render_process_handler_t *self,
        struct _cef_browser_t *browser,
        struct _cef_frame_t *frame,
        struct _cef_v8context_t *context);

/**
* @brief Permet de charger des ressource exterieur, notament graphique
* @details Return the handler for resource bundle events. If
* CefSettings.pack_loading_disabled is true (1) a handler must be returned.
* If no handler is returned resources will be loaded from pack files. This
* function is called by the browser and render processes on multiple threads.
* @param self Un poinnteur vers le handler lui meme
**/
struct _cef_resource_bundle_handler_t*
        resourceBundleHandler(struct _cef_app_t *self) ;

/**
* @brief Retourne le handler chargé de la gerstion de processus
* @details Return the handler for functionality specific to the browser process. This
* function is called on multiple threads in the browser process.
* @param self Un poinnteur vers le handler lui meme
**/
struct _cef_browser_process_handler_t*
        browserProcessHandler(struct _cef_app_t *self) ;

/**
* @brief
* @details Return the handler for functionality specific to the render process.
* This function is called on the render process main thread.
* @param self Un poinnteur vers le handler lui meme
*/

struct _cef_render_process_handler_t*
        renderProcessHandler(struct _cef_app_t *self) ;

/**
* @brief Lie tout les handlers a l'application
* @param app L'application a lié avec les handler
*/
void initializeAppHandler(cef_app_t *app);


/**
* @brief Creer une nouvelle fonction javascript a partir d'une fonction c
* @param context Contexte javascript auquelle lié la fonction
* @param nom Nom de la fonction coté javascript
* @param function La fonction c a lié au contexte javascript
*/
void createJavascriptFunction(cef_v8value_t* context, cef_string_t* nom, int (*function)(struct _cef_v8handler_t* self,
        const cef_string_t* name, struct _cef_v8value_t* object,
        size_t argumentsCount, struct _cef_v8value_t* const* arguments,
        struct _cef_v8value_t** retval, cef_string_t* exception));

/**
* @brief Genere une piece javascript a partir d'une piece coté c et la rajoute dans un tableau javascript
* @param array Tableau javascript auquelle rajouter la piece
* @param piece Piece c a convertir en javascript
* @param i indice de la piece dans le tableau
*/
void genererPiece (cef_v8value_t *array, Piece *piece, int i);


#endif