/**
* @copyright
* @file cef_app.c
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions permettant de definir les interaction de l'application avec chromium
*/

#include "./cef_app.h"


void onBeforeCommandLineProcessing(
        struct _cef_app_t *self, const cef_string_t *processType,
        struct _cef_command_line_t *commandLine) {
    /* Aucune ligne de commande a rajouter*/
}


void onRegisterCustomSchemes(
        struct _cef_app_t *self,
        struct _cef_scheme_registrar_t *registrar) {
    /* Auncun schema particulier a enregistrer */

}


void convert(char *str, cef_string_t* cefUrl) {
    char tmp[1024];
    snprintf(tmp, sizeof(tmp),"%s",str);
    cef_string_utf8_to_utf16(tmp,strlen(tmp), cefUrl);
}

static Jeu *jeu = NULL;
int checkCase (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception)  {
    int isPiece = 0;
    Case *depart;
    int ligneDepart = 0;
    int colonneDepart = 0;
    colonneDepart = arguments[0]->get_int_value(arguments[0]);
    ligneDepart = arguments[1]->get_int_value(arguments[1]);
    if (jeu->grille[colonneDepart][ligneDepart].piece) {
        depart = &jeu->grille[colonneDepart][ligneDepart];
        isPiece = depart->piece->joueur->id + 1;
    } else {
        /* Une piece n'est plus presente sur la grille mais elle l'est sur l'ui*/
    }
    *retval = cef_v8value_create_int(isPiece);
    return 1;
}







int promotion (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception)  {
    Case *arrive;
    char type;
    int ligne = 0;
    int colonne = 0;
    type = (char) arguments[0]->get_int_value(arguments[0]);
    colonne = arguments[1]->get_int_value(arguments[1]);
    ligne = arguments[2]->get_int_value(arguments[2]);
    arrive = getCase((char) colonne, (char) ligne, jeu);
    arrive->piece->type = type;
    *retval = cef_v8value_create_int(type);
    return 1;
}


int loadFile (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception) {
        GString *file = g_string_new("");
        int length = 0;
        int code = 0;
        cef_v8value_t *array;
        Option option;
        cef_string_utf16_t *nom = arguments[0]->get_string_value(arguments[0]);
        cef_string_utf8_t *nomUtf8 = calloc(1, sizeof(cef_string_utf8_t));
        length = arguments[1]->get_int_value(arguments[1]);
        cef_string_utf16_to_utf8(nom->str, (size_t) length, nomUtf8);
        file = g_string_append(file, nomUtf8->str);
        initializeJeu(jeu);
        initialize(&option);
        option.load.isOption = TRUE;
        option.load.file = file;
        code = initialiser(jeu, &option);
        array = genererListePieces();
        convert("tab", nom);
        object->set_value_bykey(object, nom, array, V8_PROPERTY_ATTRIBUTE_NONE);
        *retval = cef_v8value_create_int(code);
    return 1;
}


int saveFile (struct _cef_v8handler_t* self, const cef_string_t* name, struct _cef_v8value_t* object, size_t argumentsCount,
        struct _cef_v8value_t* const* arguments, struct _cef_v8value_t** retval, cef_string_t* exception) {
        GString *file = g_string_new("");
        int length = 0;
        cef_string_utf16_t *nom = arguments[0]->get_string_value(arguments[0]);
        cef_string_utf8_t *nomUtf8 = calloc(1, sizeof(cef_string_utf8_t));
        length = arguments[1]->get_int_value(arguments[1]);
        cef_string_utf16_to_utf8(nom->str, (size_t) length, nomUtf8);
        file = g_string_append(file, nomUtf8->str);
        file = g_string_append(file, ".echec");
        save(file, jeu);

    return 1;
}










int deplacerPiece(struct _cef_v8handler_t *self, const cef_string_t *name, struct _cef_v8value_t *object, size_t argumentsCount,
        struct _cef_v8value_t *const *arguments, struct _cef_v8value_t **retval, cef_string_t *exception) {
    Case *depart = NULL;
    Case *arrive = NULL;
    int retour = 0;
    int ligneDepart = 0;
    int colonneDepart = 0;
    int ligneArrive = 0;
    int colonneArrive = 0;
    colonneDepart = arguments[0]->get_int_value(arguments[0]);
    ligneDepart = arguments[1]->get_int_value(arguments[1]);
    colonneArrive = arguments[2]->get_int_value(arguments[2]);
    ligneArrive = arguments[3]->get_int_value(arguments[3]);
    depart = getCase((char) colonneDepart, (char) ligneDepart, jeu);
    arrive = getCase((char) colonneArrive, (char) ligneArrive, jeu);
    retour = deplace(depart, arrive, jeu);
    *retval = cef_v8value_create_int(retour);
    return 1;
}



cef_v8value_t* genererListePieces(void) {
    int taille;
    int i = 0;
    cef_v8value_t *array;
    GList *iterateur = NULL;
    Piece *piece = NULL;
    gboolean isBlanc = TRUE;
    iterateur = jeu->blanc->pieces;

    taille = g_list_length(jeu->blanc->pieces) + g_list_length(jeu->noir->pieces);
    array = cef_v8value_create_array(taille);

    while(iterateur) {
        piece = (Piece*)iterateur->data;

        genererPiece(array, piece, i);
        iterateur = iterateur->next;
        ++i;
        if (!iterateur && isBlanc) {
            isBlanc = FALSE;
            iterateur = jeu->noir->pieces;
        }
    }
    return array;
}

void genererPiece (cef_v8value_t *array, Piece *piece, int i) {
    cef_string_t *cle = calloc(1, sizeof(cef_string_t));
    cef_v8value_t *infoPiece = cef_v8value_create_object(NULL);
    cef_v8value_t *type = cef_v8value_create_int(piece->type);
    cef_v8value_t *joueur = cef_v8value_create_int(piece->joueur->id);
    cef_v8value_t *ligne = cef_v8value_create_int(piece->casePiece->ligne);
    cef_v8value_t *colonne = cef_v8value_create_int(piece->casePiece->colonne);
    convert("joueur", cle);
    infoPiece->set_value_bykey(infoPiece, cle, joueur, V8_PROPERTY_ATTRIBUTE_NONE);
    convert("ligne", cle);
    infoPiece->set_value_bykey(infoPiece, cle, ligne, V8_PROPERTY_ATTRIBUTE_NONE);
    convert("colonne", cle);
    infoPiece->set_value_bykey(infoPiece, cle, colonne, V8_PROPERTY_ATTRIBUTE_NONE);
    convert("type", cle);
    infoPiece->set_value_bykey(infoPiece, cle, type, V8_PROPERTY_ATTRIBUTE_NONE);
    array->set_value_byindex(array, i, infoPiece);
}



void onContextCreated(struct _cef_render_process_handler_t *self, struct _cef_browser_t *browser,
                        struct _cef_frame_t *frame, struct _cef_v8context_t *context) {
    Option option;
    cef_string_t *nom = calloc(1, sizeof(cef_string_t));
    cef_string_t *cefUrlFunc = calloc(1, sizeof(cef_string_t));
    cef_string_t *checkCaseNom = calloc(1, sizeof(cef_string_t));
    cef_string_t *promotionNom = calloc(1, sizeof(cef_string_t));
    cef_string_t *loadFileNom = calloc(1, sizeof(cef_string_t));
    cef_string_t *saveFileNom = calloc(1, sizeof(cef_string_t));
    cef_v8value_t *array;
    cef_v8value_t *object = context->get_global(context);
    jeu = malloc(sizeof(Jeu));
    initializeJeu(jeu);
    initialize(&option);
    initialiser(jeu, &option);
    array = genererListePieces();
    convert("tab", nom);
    object->set_value_bykey(object, nom, array, V8_PROPERTY_ATTRIBUTE_NONE);
    convert("deplacerPiece", cefUrlFunc);
    createJavascriptFunction(object, cefUrlFunc, deplacerPiece);
    convert("checkCase", checkCaseNom);
    createJavascriptFunction(object, checkCaseNom, checkCase);
    convert("promotion", promotionNom);
    createJavascriptFunction(object, promotionNom, promotion);
    convert("loadFile", loadFileNom);
    createJavascriptFunction(object, loadFileNom, loadFile);
    convert("saveFile", saveFileNom);
    createJavascriptFunction(object, saveFileNom, saveFile);
}

void createJavascriptFunction(cef_v8value_t* context, cef_string_t* nom, int (*function)(struct _cef_v8handler_t* self,
        const cef_string_t* name, struct _cef_v8value_t* object,
        size_t argumentsCount, struct _cef_v8value_t* const* arguments,
        struct _cef_v8value_t** retval, cef_string_t* exception)) {

    cef_v8handler_t* handler;
    cef_v8value_t *func;

    handler = (cef_v8handler_t*)calloc(1, sizeof(cef_v8handler_t));
    handler->base.size = sizeof(cef_v8handler_t);
    handler->execute = function;
    func = cef_v8value_create_function(nom,handler);
    context->set_value_bykey(context, nom,func, V8_PROPERTY_ATTRIBUTE_NONE);
}


struct _cef_resource_bundle_handler_t* resourceBundleHandler(struct _cef_app_t *self) {

    return NULL;
}

struct _cef_browser_process_handler_t* browserProcessHandler(struct _cef_app_t *self) {

    return NULL;
}


struct _cef_render_process_handler_t* renderProcessHandler(struct _cef_app_t *self) {
    static cef_render_process_handler_t* render = NULL;
    if (render == NULL) {
        render = (cef_render_process_handler_t*)calloc(1, sizeof(cef_render_process_handler_t));
        render->base.size = sizeof(cef_render_process_handler_t);
        initializeCefBase((cef_base_t *) render);
        render->on_context_created = onContextCreated;
    }
    return render;
}

void initializeAppHandler(cef_app_t *app) {
    app->base.size = sizeof(cef_app_t);
    initializeCefBase((cef_base_t *) app);
    app->on_before_command_line_processing = onBeforeCommandLineProcessing;
    app->on_register_custom_schemes = onRegisterCustomSchemes;
    app->get_resource_bundle_handler = resourceBundleHandler;
    app->get_browser_process_handler = browserProcessHandler;
    app->get_render_process_handler = renderProcessHandler;
}
