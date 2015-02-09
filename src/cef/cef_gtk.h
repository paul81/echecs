/**
* @copyright
* @file cef_gtk.h
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions pour lancer GTK
*/



#ifndef CEF_GTK
#define CEF_GTK

#include "include/capi/cef_app_capi.h"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

/**
* @brief Signal envoyé lors de fermeture de la fentre gtk
* @param signal Id du signal
*/
void appTerminateSignal(int signal) ;

/**
* @brief Initialise GTK
*/
void initializeGtk(void);

/**
* @brief Detruit la fenetre creer par GTK
* @param widget Fenetre a detruire
* @param data Donnée supplementaire pour la fermeture
*/
void windowDestroySignal(GtkWidget *widget, gpointer data);

/**
* @brief Creer la fenetre avec GTK
* @param title Titre de la fennetre
* @param width largeur de la fenetre
* @param height hauteur de la fenetre
*/
GtkWidget*createGtkWindow(char *title, int width, int height);

#endif