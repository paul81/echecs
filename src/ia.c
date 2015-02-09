/**
* @copyright
* @file ia.c
* @author Boutes Paul, Cassan Damien
* @brief Implementation de toutes fonctions relative a l'intelligence artificielle
*/
#include "./ia.h"

static GMutex mutex;
static GCond gcond;


GList* positionToDeplacement(Case *depart, GList* positions, Jeu *jeu) {

    GList *iterateur = positions;
    Position *position;
    Deplacement *deplacement = NULL;
    GList *listeDeplacement = NULL;
    char a = 0;
    char b = 0;
    while (iterateur) {
        position = (Position*)iterateur->data;
        deplacement = malloc(sizeof(Deplacement));
        deplacement->depart = depart;
        a = position->colonne;
        b = position->ligne;
        deplacement->arriver = getCase(a, b, jeu);
        listeDeplacement = g_list_append(listeDeplacement, deplacement);

        iterateur = iterateur->next;
    }

    return listeDeplacement;
}

GList* genererToutesLesPositions(Jeu *jeu) {
    GList *listePiece = NULL, *listeDeplacement = NULL, *positions = NULL, *toutesLesPositions = NULL, *iterateurPosition = NULL;
    Piece *piece = NULL;
    if (jeu->tour == 0) {
        listePiece = jeu->blanc->pieces;
    } else {
        listePiece = jeu->noir->pieces;
    }
    iterateurPosition = listePiece;
    while (iterateurPosition) {
        piece = (Piece*) iterateurPosition->data;
        positions = genererPosition(piece->casePiece, jeu);
        positions = check(positions, jeu);
        listeDeplacement = positionToDeplacement(piece->casePiece, positions, jeu);
        toutesLesPositions = g_list_concat(toutesLesPositions, listeDeplacement);
        iterateurPosition = iterateurPosition->next;
        g_list_free_full(positions, &freeElement);
        positions = NULL;
    }
    return toutesLesPositions;
}

int parcoursNegamax (GList *deplacements, int score, int max, int alpha, int beta, Jeu *jeu, int profondeur,
                    int joueur, struct fann *neural_network) {
    GList *iterateur = deplacements;
    Deplacement *deplacement = NULL;
    Piece *piecePrise = NULL, *pieceDeplacer =NULL;
    while (iterateur) {
        deplacement = (Deplacement*) iterateur->data;
        pieceDeplacer = deplacement->depart->piece;
        piecePrise = effectuerDeplacement(jeu, deplacement->depart, deplacement->arriver);
        score = - negamaxAlpha(jeu, profondeur - 1, -joueur, -beta, -alpha, neural_network);
        if (score > max) {
            max = score;
        }
        annulerDeplacement(deplacement->depart, deplacement->arriver, jeu, piecePrise, pieceDeplacer);
        if (max > alpha) {
            alpha = max;
        }
        if (alpha > beta) {
            iterateur = NULL;
        } else {
            iterateur = iterateur->next;
        }
    }
    return max;
}
int negamaxAlpha(Jeu *jeu, int profondeur, int joueur, int alpha, int beta, struct fann *neural_network) {

    /* Avec cette algorithme une grande valeur de evaluerPos est favorable au joueur A peut importe le tour*/
    /* evaluerJeu renvoie une grande valeur si le joueur A gagne, une petite valeur sinon */
    int score = 0, max = -100000;
    GList *deplacements = NULL;
    changerTour(jeu);
    deplacements = genererToutesLesPositions(jeu);

    if (profondeur == 0) {
        max =  joueur * evaluerJeu(jeu, neural_network);
    } else {

      max = parcoursNegamax(deplacements, score, max, alpha, beta, jeu, profondeur, joueur, neural_network);
    }

    if (deplacements) {
        g_list_free_full(deplacements, &freeElement);
        deplacements = NULL;
    }
    changerTour(jeu);
    return max;
}


void annulerDeplacement(Case *depart, Case *arriver, Jeu * jeu, Piece *piecePrise, Piece *pieceDeplacer) {
    depart->piece = pieceDeplacer;
    pieceDeplacer->casePiece = depart;
    arriver->piece = NULL;

    if (piecePrise) {
        if (jeu->tour == 0)
        {
            jeu->noir->pieces = g_list_append(jeu->noir->pieces, piecePrise);
        } else {
            jeu->blanc->pieces = g_list_append(jeu->blanc->pieces, piecePrise);
        }
        piecePrise->casePiece->piece = piecePrise;
    }
}

int convertPieceToVal (char piece) {
    int retour = 0;
    switch (piece) {
        case 'P': retour = 1; break;
        case 'C': retour = 2; break;
        case 'T': retour = 3; break;
        case 'D': retour = 5; break;
        case 'R': retour = 6; break;
        case 'F': retour = 4; break;
            default: retour = 0; break;
    }

    return retour;
}

int evaluerPiece (char piece) {
    int retour = 0;
    switch (piece) {
        case 'P': retour = 1; break;
        case 'C': retour = 4; break;
        case 'T': retour = 5; break;
        case 'D': retour = 10; break;
        case 'R': retour = 100; break;
        case 'F': retour = 4; break;
        default: retour = 0; break;
    }

    return retour;
}

int evaluerToutesLesPieces(Jeu *jeu) {
    int total = 0;
    GList* iterateur = NULL;
    Piece *piece = NULL;
    iterateur = jeu->blanc->pieces;
    while(iterateur) {
        piece = iterateur->data;
        total += evaluerPiece(piece->type) * 200;
        iterateur = iterateur->next;
    }
    iterateur = jeu->noir->pieces;
    while(iterateur) {
        piece = iterateur->data;
        total -= evaluerPiece(piece->type) * 200;
        iterateur = iterateur->next;
    }
    return total;
}

int evaluerJeu(Jeu *jeu, struct fann *neural_network) {

    fann_type tab[64];
    int i, j, valeur = 0, total = 0;
    float *out;
    total += evaluerToutesLesPieces(jeu);

    for (i = 0; i < 8; ++i) {
        for (j = 0; j < 8 ; j++) {
            valeur = 0;
            if (jeu->grille[i][j].piece)
                valeur = convertPieceToVal(jeu->grille[i][j].piece->type) * (-1 + 2 * jeu->tour);
            tab[i * 8 + j] = valeur;
        }
    }

    out = fann_run(neural_network, tab);
    out[0] *= 10000.f;
    total += out[0];
    if (jeu->tour == 1)
        total = -total;
    return total;
}

void changerTour (Jeu *jeu) {
    if (jeu->tour == 0) {
        jeu->tour = 1;
    } else {
        jeu->tour = 0;
    }
}


void ia_thread(gpointer data) {
    int score = 0;
    gboolean echec = FALSE;
    ThreadArguments *arg = (ThreadArguments*)data;
    Jeu *jeu = arg->jeu;
    int joueur = -1 + 2 * jeu->tour;
    echec = isEchec(jeu, jeu->tour);
    if (!echec) {
        struct fann *neural_network = fann_create_from_file(arg->neural_network_file->str);
        score = -negamaxAlpha(jeu,4, joueur,-100000,100000, neural_network);
        fann_destroy(neural_network);
    }
    g_mutex_lock(&mutex);
    (*arg->count_thread)++;
    if(score > *arg->score && !echec) {
        *arg->score = score;
        *arg->bestMove = arg->move;
    }
    g_cond_signal(&gcond);
    g_mutex_unlock(&mutex);

}

void copierJeux(Jeu *original, Jeu *copy) {

    GString *hash1 = NULL, *hash2 = NULL;
    hash1 = createHash(original->blanc->pieces);
    hash2 = createHash(original->noir->pieces);
    copy->tour = original->tour;
    copy->positionInitialeTour1Blanc = 0;
    copy->positionInitialeTour1Noir = 0;
    copy->positionInitialeTour2Blanc = 0;
    copy->positionInitialeTour2Noir = 0;
    copy->prise = 0;
    copy->positionPriseCol = 0;
    copy->positionPriseLigne = 0;
    copy->historique = NULL;
    copy->historique = g_hash_table_new(g_str_hash, g_str_equal);
    initializeGrille(copy, copy->blanc, hash1);
    initializeGrille(copy, copy->noir, hash2);

}

GString *loadNeuralNetwork(Option *option) {
    GString *neural_network_file = NULL;
    int fd = -1;

    if (option->base.isOption) {
        neural_network_file = option->base.file;
        fd = g_open(neural_network_file->str, O_RDONLY);
        if (fd < 0) {
            printf("Erreur lors de l'ouverture du fichier de base d'ouverture\n");
            exit(8);
        }
        close(fd);
    } else {
        neural_network_file = g_string_new("bin/xor_float.net");
    }

    return neural_network_file;
}

Jeu* initialiserNJeux(int nb_coups, Jeu *jeu) {

    Jeu *copyJeu = (Jeu*) malloc(nb_coups * sizeof(Jeu));
    int i = 0;

    for (i = 0; i < nb_coups ; ++i) {
        initializeJeu(&copyJeu[i]);
        copierJeux(jeu, &copyJeu[i]);
    }

    return copyJeu;
}

void lancerIA(int nb_coups, Jeu* copyJeu, Deplacement** bestMove, int *count_thread, int *score, GString *neural_network_file, GList *positions) {
    int i = 0;
    Deplacement *deplacement;
    Case *depart =NULL, *arriver = NULL;
    ThreadArguments *threadArguments = malloc(sizeof(ThreadArguments) * nb_coups);
    for (i = 0; i < nb_coups; ++i) {

        deplacement = (Deplacement*) g_list_nth(positions, i)->data;
        threadArguments[i].jeu = &copyJeu[i];
        threadArguments[i].bestMove = bestMove;
        threadArguments[i].count_thread = count_thread;
        threadArguments[i].score = score;
        threadArguments[i].move = deplacement;
        threadArguments[i].neural_network_file = neural_network_file;
        depart = &copyJeu[i].grille[deplacement->depart->colonne][deplacement->depart->ligne];
        arriver = &copyJeu[i].grille[deplacement->arriver->colonne][deplacement->arriver->ligne];
        effectuerDeplacement(&copyJeu[i], depart, arriver);
        g_thread_new("ia_thread", (GThreadFunc) ia_thread, &threadArguments[i]);
    }
}


int playIA (Jeu *jeu, Option *option) {
    GList *positions = NULL;
    Deplacement *bestMove = NULL;
    GString *neural_network_file = NULL;
    int score = -100000;
    int nb_coups = 0, count_thread = 0;
    Jeu *copyJeu = NULL;
    neural_network_file = loadNeuralNetwork(option);
    positions = genererToutesLesPositions(jeu);
    nb_coups = g_list_length(positions);
    copyJeu = initialiserNJeux(nb_coups, jeu);
    lancerIA(nb_coups, copyJeu, &bestMove, &count_thread, &score, neural_network_file, positions);
    while( count_thread < nb_coups)
        g_cond_wait(&gcond, &mutex);

    if (bestMove) {
        effectuerDeplacement(jeu, bestMove->depart, bestMove->arriver);
        changerTour(jeu);
        printf("Le deplacement a correctement été effectuer par l'IA \n");
    } else {
        printf("fin du jeux !");
    }
    return 0;
}