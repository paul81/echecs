/**
 * @copyright 
 * @file structure.h
 * @author Boutes Paul, Cassan Damien
 * @brief permet de gérer l'affichage graphique du programme
 */




#include "./ui.h"


cef_app_t initUI(int argc, char **argv) {
    cef_main_args_t mainArgs;
    cef_app_t app;
    int code;
    mainArgs.argc = argc;
    mainArgs.argv = argv;
    initializeAppHandler(&app);
    code = cef_execute_process(&mainArgs, &app, NULL);
    if (code >= 0) {
        printf("erreur code chrome >= 0");
    }
    return app;
}


void startUI(int argc, char **argv, cef_app_t app) {
    GtkWidget* hwnd;
    cef_window_info_t *windowInfo = calloc(1, sizeof(cef_window_info_t));
    cef_string_t *cefUrl = calloc(1, sizeof(cef_string_t));
    cef_client_t client;
    cef_browser_settings_t *browserSettings = calloc(1, sizeof(cef_browser_settings_t));
    cef_main_args_t mainArgs;
    cef_settings_t *settings = calloc(1, sizeof(cef_settings_t));
    mainArgs.argc = argc;
    mainArgs.argv = argv;
    setCefOption(settings, browserSettings);
    cef_initialize(&mainArgs, settings, &app, NULL);
    initializeGtk();
    hwnd = createGtkWindow("Jeux d'echecs", 700, 844);
    windowInfo->parent_widget = hwnd;
    getPath(cefUrl);
    browserSettings->size = sizeof(cef_browser_settings_t);
    browserSettings->file_access_from_file_urls = STATE_ENABLED;
    initialize_client_handler(&client);
    cef_browser_host_create_browser(windowInfo, &client, cefUrl, browserSettings, NULL);
    cef_run_message_loop();
    cef_shutdown();
}

void setCefOption(cef_settings_t* settings, cef_browser_settings_t *browserSettings) {
    settings->size = sizeof(cef_settings_t);
    settings->no_sandbox = 1;
    settings->log_severity = LOGSEVERITY_DISABLE;
    settings->command_line_args_disabled = 1;
    settings->remote_debugging_port = 9000;
    browserSettings->plugins = STATE_DISABLED;
}
void getPath (cef_string_t *cefUrl) {
    char appPath[1024];
    ssize_t ppLen;
    char url[1024];
    ppLen = readlink("/proc/self/exe", appPath, sizeof(appPath)-1);
    if (ppLen != -1 && ppLen > 0) {
        appPath[ppLen] = '\0';
        do {
            ppLen -= 1;
            appPath[ppLen+1] = '\0';
        } while (appPath[ppLen] != '/' && ppLen > 0);

        if (ppLen > 0 && appPath[ppLen] == '/') {
            appPath[ppLen] = '\0';
        }
    }
    snprintf(url, sizeof(url), "file://%s/www/index.html",appPath   );
    cef_string_utf8_to_utf16(url, strlen(url), cefUrl);
}