/**
* @copyright
* @file cef_gtk.c
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions pour lancer GTK
*/


#include "./cef_gtk.h"

void appTerminateSignal(int signatl) {
    cef_quit_message_loop();
}

void initializeGtk(void) {
    gtk_init(0, NULL);
    signal(SIGINT, appTerminateSignal);
    signal(SIGTERM, appTerminateSignal);
}

void windowDestroySignal(GtkWidget *widget, gpointer data) {
    cef_quit_message_loop();
}

GtkWidget*createGtkWindow(char *title, int width, int height) {

    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget* vbox;

    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(windowDestroySignal), NULL);

    gtk_window_set_default_size(GTK_WINDOW(window),
            width, height);

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    gtk_window_set_title(GTK_WINDOW(window), title);

    vbox = gtk_vbox_new(0, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    gtk_widget_show_all(window);

    return vbox;
}