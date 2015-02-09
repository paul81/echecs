/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien
 * @brief Permet de gérer les options passé en ligne de commande
 * 
 */

#include "./option.h"


int setIaLevel(IaLevel *level, int n) {
    int code;
    int const codeNum = 20;
    if (level->param >= '1' && level->param <= '3') {
        printf("Definit le niveau de l'IA à %c pour le joueur %d\n",level->param,n);
        code = 0;
    } else {
        code = codeNum;
    }
    return code;
}

void setIaPlayer(Ia *player) {
        printf("Definit le joueur %d comme étant gérer par l'ordinateur\n",player->param);
}



Option command(int argc, char **argv) {
        int option = 0;
        Option data;
        initialize(&data);
        do {
                int optionIndex = 0;
                static struct option longOptions[] = {
                        {"help", no_argument, 0, 'h'},
                        {"h", no_argument, 0, 'h' },
                        {"l", required_argument, 0, 'l' },
                        {"l1", required_argument, 0, 256 },
                        {"l2", required_argument, 0, 257 },
                        {"s", required_argument, 0, 's'},
                        {"d", required_argument, 0, 'd'},
                        {"p", required_argument, 0, 'p'},
                        {"a", required_argument, 0, 'a'},
                        {"c1", no_argument, 0, 258},
                        {"c2", no_argument, 0, 259}
                };
                /*récupération de la ligne de commande*/
                option = getopt_long_only(argc, argv, "", longOptions, &optionIndex);
                switch (option) {
                case 'h':
                        data.help.isOption = TRUE;
                        break;
                case 'l':
                        data.load.file = g_string_new(optarg);
                        data.load.isOption = TRUE;
                        break;
                case 's':
                        data.save.file = g_string_new(optarg);
                        data.save.isOption = TRUE;
                        break;
                case 'd':
                        data.base.file = g_string_new(optarg);
                        data.base.isOption = TRUE;
                        break;
                case 'p':
                        if (!data.piece.isOption) {
                            copyPosition(&data, FALSE);
                        }
                        break;
                case 'a':
                        if (!data.piece.isOption) {
                            copyPosition(&data, TRUE);
                        }
                        break;
                case 256:
                            data.level1.param = optarg[0];
                            data.level1.isOption = TRUE;
                        break;
                case 257:
                            data.level2.param = optarg[0];
                            data.level2.isOption = TRUE;
                        break;
                case 258:
                        data.ia1.param = 1;
                        data.ia1.isOption = TRUE;
                        break;
                case 259:
                        data.ia2.param = 2;
                        data.ia2.isOption = TRUE;
                        break;
                case -1:
                        break;
                default:
                        printf("Commande inconnue ! \n");
                        break;
                }
        } while (option >= 0);

        return data;
}





void initialize(Option *data) {
        data->help.isOption = FALSE;
        data->load.isOption = FALSE;
        data->save.isOption = FALSE;
        data->base.isOption = FALSE;
        data->piece.isOption = FALSE;
        data->piece.isAlgebrique = FALSE;
        data->level1.isOption = FALSE;
        data->level2.isOption = FALSE;
        data->ia1.isOption = FALSE;
        data->ia2.isOption = FALSE;
        data->load.file = NULL;
        data->save.file = NULL;
        data->base.file = NULL;
        data->piece.param1 = NULL;
        data->piece.param2 = NULL;
        data->level1.param = 0;
        data->level2.param = 0;
        data->ia1.param = 0;
        data->ia2.param = 0;
        data->piece.isRoque = 0;
}

int transformPosition (int position) {
    int retour = 0;
    switch (position) {
        case 0: retour = 7; break;
        case 1: retour = 6; break;
        case 2: retour = 5; break;
        case 3: retour = 4; break;
        case 4: retour = 3; break;
        case 5: retour = 2; break;
        case 6: retour = 1; break;
        case 7: retour = 0; break;
        default: retour = 0; break;

    }

    return retour;

}

void copyPosition(Option *data, gboolean algebrique) {
    int taille;
    char *buffer = NULL;
    const char s[] = "-";
    char *token = NULL;
    taille = strlen(optarg);
    if (5 == taille && !algebrique) {
        token = strtok_r(optarg, s, &buffer);
        data->piece.param1 = g_string_new(token);
        token = strtok_r(NULL, s, &buffer);
        data->piece.param2 = g_string_new(token);
        data->piece.isOption = TRUE;

    } else if(algebrique)
    {
        copyPositionAlgebrique(taille, token, data);
    }
    else {

        printf("Mauvais paramètre ! \n");
    }
}

void isRoqueAlgebrique(int taille, char* token, Option *data)
{
    if (taille == 3 && token[0] == '0' && token[1] == '-' && token[2] == '0') {
        data->piece.isRoque = 1;
        data->piece.isAlgebrique = FALSE;
    } else if (taille == 5 && token[0] == '0' && token[2] == '0' && token[4] == '0') {
        data->piece.isAlgebrique = FALSE;
        data->piece.isRoque = 2;
    } else {
        data->piece.isRoque = 0;
    }
}

void copyPositionAlgebrique (int taille, char* token, Option *data) {
    const char s[] = "-";
    char *buffer;
    if (6 == taille) {
        token = strtok_r(optarg, s, &buffer);
        data->piece.param1 = g_string_new(token+1);
        token = strtok_r(NULL, s, &buffer);
        data->piece.param2 = g_string_new(token);
        data->piece.isOption = TRUE;
    }
    if (3 == taille) {
        data->piece.param1 = g_string_new(optarg+1);
        data->piece.code = optarg[0];
        data->piece.isOption = TRUE;
        data->piece.isAlgebrique = TRUE;
    }
    isRoqueAlgebrique(taille, optarg, data);
}
void freeElement(gpointer data) {
    free(data);
}

void freeValue(Jeu *jeu, Option *data) {
    freeOption(data);
    freeJeu(jeu);
}

void freeOption(Option *data) {
    if (data->piece.param1) {
        g_string_free(data->piece.param1, TRUE);
    }
    if (data->piece.param2) {
        g_string_free(data->piece.param2, TRUE);
    }
    if (data->load.file) {
        g_string_free(data->load.file, TRUE);
    }
    if (data->save.file) {
        g_string_free(data->save.file, TRUE);
    }
    if (data->base.file) {
        g_string_free(data->base.file, TRUE);
    }
}

void freeJeu (Jeu *jeu) {
    int i = 0;
    const int length = 8;

    if (jeu->grille) {
        for (i = 0; i < length; i++) {
            free(jeu->grille[i]);
        }
        free(jeu->grille);
    }
    if (jeu->blanc->pieces) {
        g_list_free_full(jeu->blanc->pieces, &freeElement);
        jeu->blanc->pieces = NULL;
    }
    if (jeu->noir->pieces) {
        g_list_free_full(jeu->noir->pieces, &freeElement);
        jeu->noir->pieces = NULL;
    }
    if (jeu->blanc) {
        free(jeu->blanc);
    }
    if (jeu->noir) {
        free(jeu->noir);
    }
}