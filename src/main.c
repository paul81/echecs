/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien
 * @brief Fichier permettant de démarrer le programme, lance le jeu
 */


#include "./jeu.h"
#include "./ui.h"


int main(int argc, char **argv) {
    Option data;
    Jeu jeu;
    int errorCode = 0;
    cef_app_t app;

    if (argc == 1 || !strcmp(argv[1], "--type=zygote") || !strcmp(argv[1], "--type=gpu-process")) {
        app = initUI(argc, argv);
        startUI(argc, argv, app);
    } else {
        initializeJeu(&jeu);
        data = command(argc, argv);
        errorCode = initialiser(&jeu, &data);
        if (!errorCode) {
            errorCode = jouer(&jeu, &data);
        }
        freeValue(&jeu, &data);
    }
    return errorCode;
}

