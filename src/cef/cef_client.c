/**
* @copyright
* @file cef_client.c
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions de callback utiliser par chromium
*/

#include "./cef_client.h"



struct _cef_display_handler_t* CEF_CALLBACK get_display_handler(struct _cef_client_t* self) {
    return NULL;
}



struct _cef_drag_handler_t* CEF_CALLBACK get_drag_handler(
        struct _cef_client_t* self) {
    return NULL;
}


struct _cef_focus_handler_t* CEF_CALLBACK get_focus_handler(
        struct _cef_client_t* self) {
    return NULL;
}



struct _cef_keyboard_handler_t* CEF_CALLBACK get_keyboard_handler(
        struct _cef_client_t* self) {
    return NULL;
}


struct _cef_life_span_handler_t* CEF_CALLBACK get_life_span_handler(
        struct _cef_client_t* self) {
    return NULL;
}


struct _cef_load_handler_t* CEF_CALLBACK get_load_handler(
        struct _cef_client_t* self) {
    return NULL;
}


struct _cef_render_handler_t* CEF_CALLBACK get_render_handler(
        struct _cef_client_t* self) {
    return NULL;
}


struct _cef_request_handler_t* CEF_CALLBACK get_request_handler(
        struct _cef_client_t* self) {
    return NULL;
}

struct _cef_dialog_handler_t* CEF_CALLBACK get_dialog_handler(
        struct _cef_client_t* self) {
    return NULL;
}


int CEF_CALLBACK on_process_message_received(
        struct _cef_client_t* self,
        struct _cef_browser_t* browser, cef_process_id_t source_process,
        struct _cef_process_message_t* message) {
    return 0;
}


void initialize_client_handler(cef_client_t* client) {

    client->base.size = sizeof(cef_client_t);
    initializeCefBase((cef_base_t *) client);
    client->get_dialog_handler = get_dialog_handler;
    client->get_display_handler = get_display_handler;
    client->get_drag_handler = get_drag_handler;
    client->get_focus_handler = get_focus_handler;
    client->get_keyboard_handler = get_keyboard_handler;
    client->get_life_span_handler = get_life_span_handler;
    client->get_load_handler = get_load_handler;
    client->get_render_handler = get_render_handler;
    client->get_request_handler = get_request_handler;
    client->on_process_message_received = on_process_message_received;
}

