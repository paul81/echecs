/**
* @copyright
* @file ui.h
* @author Boutes Paul, Cassan Damien
* @brief Definit toutes fonctions relative au lancement de l'interface graphique
*/

#ifndef UI
#define UI

#include "./cef/cef_gtk.h"
#include "./cef/cef_client.h"
#include "./cef/cef_app.h"

/**
* @brief Initialise Chromium, notament en lancant les sous processus pour le gpu et le reseau
* @param argc Nombre d'arguments passé au programme
* @param argv Arguments passé au programme
* @return Une application chromium initialisé
*/
cef_app_t initUI(int argc, char **argv);

/**
* @brief Lance l'interface graphique
* @param argc Nombre d'arguments passé au programme
* @param argv Arguments passé au programme
* @param app Application chromium initialisé avec initUI
*/
void startUI(int argc, char **argv, cef_app_t app);

/**
* @brief recupere le chemin jusqu'a l'executable
* @param cefUrl Une chaine encodé en UTF16 complété par la fonction
*/
void getPath (cef_string_t *cefUrl);

/**
* @brief Définit les options d'execution de chromium
* @param settings Les options globale de chromium
* @param browserSettings Les optionns relative au navigateur (javascript, affichage)
*/
void setCefOption(cef_settings_t* settings, cef_browser_settings_t *browserSettings);

#endif