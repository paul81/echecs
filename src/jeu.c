/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien
 * @brief Fichier permettant d'initialiser et de lancer le jeu
 */
#include "./jeu.h"


int displayHelp(void) {
    /* Il y a deux printf car il y a plus de 500 caractéres dans la string 
    et cela declenche un warning a la compilation */
    printf("Commande disponible : \n"
            "-h, --help      : Affiche de l'aide\n"
            "-l file         : Charge le jeu depuis le fichier file\n"
            "-s file         : Sauvegarde le jeu sur le fichier file\n"
            "-d file         : Utilise le fichier file comme base de donnnée d'ouverture\n");
    printf("-p \?\?-\?\?        : Déplace la pièce de la case ?? à la case ??\n"
            "-a \?[\?\?-]\?\?     : Déplace la pièce avec la notation algébrique\n"
            "-c1             : Définit le joueur un comme étant gérer par l'ordinateur\n"
            "-c2             : Définit le joueur un comme étant gérer par l'ordinateur\n"
            "-l1 [1,2,3]     : Définit le niveau de l'IA pour le joueur 1\n"
            "-l2 [1,2,3]     : Définit le niveau de l'IA pour le joueur 2\n");
    return 1;
}

int initialiser(Jeu *jeu, Option *option) {
    GString *hash1 = g_string_new("");
    GString *hash2 = g_string_new("");
    int errorCode = 0;
    if (option->help.isOption) {
        errorCode = displayHelp();
    }
    if (!errorCode) {
        errorCode = setOption(option, jeu, hash1, hash2);
    }
    initializeGrille(jeu, jeu->blanc, hash1);
    initializeGrille(jeu, jeu->noir, hash2);
    g_string_free(hash1, TRUE);
    g_string_free(hash2, TRUE);
    return errorCode;
}

void setNewGame(Jeu *jeu, GString *hash1, GString *hash2) {
    jeu->tour = 0;
    jeu->positionInitialeTour1Blanc = 1;
    jeu->positionInitialeTour1Noir = 1;
    jeu->positionInitialeTour2Blanc = 1;
    jeu->positionInitialeTour2Noir = 1;
    jeu->prise = '0';
    jeu->positionPriseCol = 'A';
    jeu->positionPriseLigne = '1';
    jeu->historique = NULL;
    jeu->historique = g_hash_table_new(g_str_hash, g_str_equal);
    hash1 = g_string_append(hash1, "Ta8Cb8Fc8Dd8Re8Ff8Cg8Th8Pa7Pb7Pc7Pd7Pe7Pf7Pg7Ph7");
    hash2 = g_string_append(hash2, "Ta1Cb1Fc1Dd1Re1Ff1Cg1Th1Pa2Pb2Pc2Pd2Pe2Pf2Pg2Ph2");
}

int setOption(Option *option, Jeu *jeu, GString *hash1, GString *hash2) {
    int errorCode = 0;
    if (option->level1.isOption ) {
        errorCode = setIaLevel(&option->level1, 1);
    }
    if (option->level2.isOption && errorCode == 0) {
        setIaLevel(&option->level2, 1);
    }
    if (option->ia1.isOption && errorCode == 0) {
        setIaPlayer(&option->ia1);
    }
    if (option->ia2.isOption && errorCode == 0) {
        setIaPlayer(&option->ia2);
    }
    if (option->load.isOption && errorCode == 0) {
        jeu->historique = g_hash_table_new(g_str_hash, g_str_equal);
        errorCode = load(option->load.file, jeu, hash1, hash2);
    } else {
        setNewGame(jeu, hash1, hash2);
    }
    if (option->base.isOption && errorCode == 0) {
        base(option->base.file);
    }
    return errorCode;
}

int deplacementAlgebrique(Jeu *jeu, Option *option, Case* arrive) {
    GList *iterateur = NULL;
    Piece *piece = NULL;
    Case *depart = NULL;
    int retour = 1;
    if (jeu->tour == 0) {
        iterateur = jeu->blanc->pieces;
    } else {
        iterateur = jeu->noir->pieces;
    }
    while (iterateur) {
        piece = (Piece *) iterateur->data;
        if (piece->type == option->piece.code) {
            depart = piece->casePiece;
            retour = deplace(depart, arrive, jeu);
            if (retour == 0 || (retour >= 200 && retour <= 203)) {
                iterateur = NULL;
            }
        }
        if (iterateur) {
            iterateur = iterateur->next;
        }
    }
    return retour;
}

int changerPiecePromotion(Piece *piece)
{
    int retour = 0;
    char reponse = 0;
    printf("Par quelle piece vouler vous remplacer votre pion (D,F,C,T) ?  \n");
    scanf("%c", &reponse);
    printf("\n");
    switch (reponse) {
        case 'D':
        case 'F':
        case 'C':
        case 'T':
            retour = 0;
            break;
        default:
            retour = 1;
            break;
    }
    if (!retour)
    {
        piece->type = reponse;
    }

    return retour;

}

int effectuerPromotion (Jeu *jeu, int retour) {
    GList *iterateur = NULL;
    Piece *piece = NULL;
    int ligne = 0;
    if (retour == 300) {
        iterateur = jeu->blanc->pieces;
    } else {
        iterateur = jeu->noir->pieces;
        ligne = 7;
    }
    while (iterateur) {
        piece = (Piece*)iterateur->data;
        if (piece->type == 'P' && piece->casePiece->ligne == ligne) {
            iterateur = NULL;
            do {
                retour = changerPiecePromotion(piece);
            } while(retour);
        } else {
            iterateur = iterateur->next;
        }
    }

    retour = 0;
    return retour;
}

void roqueDepuisNotationAlgebrique (Jeu *jeu, Option *option) {
    if (option->piece.isRoque == 1) {
        if (jeu->tour) {
            option->piece.param1 = g_string_new("e1");
            option->piece.param2 = g_string_new("g1");
        } else {
            option->piece.param1 = g_string_new("e8");
            option->piece.param2 = g_string_new("g8");
        }
    } if (option->piece.isRoque == 2) {
        if (jeu->tour) {
            option->piece.param1 = g_string_new("e1");
            option->piece.param2 = g_string_new("c1");
        } else {
            option->piece.param1 = g_string_new("e8");
            option->piece.param2 = g_string_new("c8");
        }
    }
}

int jouer(Jeu *jeu, Option *option) {
    int retour = 0;
    Case* depart = NULL;
    Case* arrive = NULL;
    Move *piece = &option->piece;
    if (option->ia1.isOption && jeu->tour == 0) {
        playIA(jeu, option);
    } else if (option->ia2.isOption && jeu->tour == 1) {
        playIA(jeu, option);
    } else if (option->piece.isOption) {
        if (option->piece.isAlgebrique) {
            arrive = getCase((char) (option->piece.param1->str[0] - 'a'),
                    (char) transformPosition(option->piece.param1->str[1] - '1'), jeu);
            retour = deplacementAlgebrique(jeu, option, arrive);
        } else {
            roqueDepuisNotationAlgebrique(jeu, option);
            depart = getCase((char) (piece->param1->str[0] - 'a'), (char) transformPosition(piece->param1->str[1] - '1'), jeu);
            arrive = getCase((char) (piece->param2->str[0] - 'a'), (char) transformPosition(piece->param2->str[1] - '1'), jeu);
            retour = deplace(depart, arrive, jeu);
            if (retour >= 300 && retour <= 301) {
                retour = effectuerPromotion(jeu, retour);
            }
        }
    }
    if (option->save.isOption && !retour) {
        save(option->save.file, jeu);
    }
    return retour;
}