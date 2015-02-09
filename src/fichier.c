/**
 * @copyright
 * @author Boutes Paul, Cassan Damien
 * @file fichier.c
 * @brief Contient le code des fonctions manipulant des fichiers
 */
#include <zlib.h>
#include "./fichier.h"



int load(GString *file, Jeu *jeu, GString *ghash1, GString *ghash2) {
    int fd = g_open(file->str, O_RDONLY);
    int retour = 0;
    if (fd < 0) {
        printf("Erreur lors de l'ouverture du fichier \n");
        retour = 52;
    } else {
        read(fd, &jeu->tour, sizeof(jeu->tour));
        read(fd, &jeu->prise, sizeof(jeu->prise));
        read(fd, &jeu->positionPriseCol, sizeof(jeu->positionPriseCol));
        read(fd, &jeu->positionPriseLigne, sizeof(jeu->positionPriseLigne));
        read(fd, &jeu->positionInitialeTour1Blanc, sizeof(jeu->positionInitialeTour1Blanc));
        read(fd, &jeu->positionInitialeTour2Blanc, sizeof(jeu->positionInitialeTour2Blanc));
        read(fd, &jeu->positionInitialeTour1Noir, sizeof(jeu->positionInitialeTour1Noir));
        read(fd, &jeu->positionInitialeTour2Noir, sizeof(jeu->positionInitialeTour2Noir));
        readHash(fd, ghash1);
        readHash(fd, ghash2);
        readHashTable(fd, jeu->historique);
        close(fd);
    }
    return retour;
}

void readHash(int fd, GString* ghash) {
    int sizehash = 0;
    char *hash = NULL;
    read(fd, &sizehash, sizeof(sizehash));
    hash = malloc((size_t) sizehash);
    read(fd, hash, (size_t) sizehash);
    ghash = g_string_append(ghash, hash);
    free(hash);
}

void writeHash(int fd, GString *hash) {
        int size = strlen(hash->str) + 1;
        write(fd, &size, sizeof(size));
        size = write(fd, hash->str, (size_t) size);
}





void writeHashTable(int fd, GHashTable *table) {
    GList *listKey = NULL;
    GList *listVal = NULL;
    int size = 0;
    int val = 0;
    int sizeHash = 0;
    int i = 0;
    listKey = g_hash_table_get_keys(table);
    listVal = g_hash_table_get_values(table);
    size = g_list_length(listKey);
    write(fd, &size, sizeof(size));
    for (i = 0; i < size; ++i) {
        sizeHash = strlen(listKey->data) + 1;
        write(fd, &sizeHash, sizeof(sizeHash));
        write(fd, (char *) listKey->data, (size_t) sizeHash);
        val = GPOINTER_TO_INT(listVal->data);
        write(fd, &val, sizeof(int));
        listKey = listKey->next;
        listVal = listVal->next;
    }
}

void readHashTable(int fd, GHashTable *table) {
    int size = 0;
    int sizeHash = 0;
    int i = 0;
    char *hash = NULL;
    int val = 0;
    read(fd, &size, sizeof(size));
    for (i = 0; i < size; ++i) {
        read(fd, &sizeHash, sizeof(sizeHash));
        hash = malloc((size_t) sizeHash);
        read(fd, hash, (size_t) sizeHash);
        read(fd, &val, sizeof(int));
        g_hash_table_insert(table, hash, GINT_TO_POINTER(val));
    }

}



void save(GString *file, Jeu *jeu) {
        int fd;
        GString *hash1 = NULL;
        GString *hash2 = NULL;
        fd = g_open(file->str, O_CREAT|O_RDWR|O_TRUNC, S_IRWXU);
        if (fd < 0) {
                printf("Erreur\n");
        } else {
            write(fd, &jeu->tour, sizeof(jeu->tour));
            write(fd, &jeu->prise, sizeof(jeu->prise));
            write(fd, &jeu->positionPriseCol, sizeof(jeu->positionPriseCol));
            write(fd, &jeu->positionPriseLigne, sizeof(jeu->positionPriseLigne));
            write(fd, &jeu->positionInitialeTour1Blanc, sizeof(jeu->positionInitialeTour1Blanc));
            write(fd, &jeu->positionInitialeTour2Blanc, sizeof(jeu->positionInitialeTour2Blanc));
            write(fd, &jeu->positionInitialeTour1Noir, sizeof(jeu->positionInitialeTour1Noir));
            write(fd, &jeu->positionInitialeTour2Noir, sizeof(jeu->positionInitialeTour2Noir));
            hash1 = createHash(jeu->blanc->pieces);
            hash2 = createHash(jeu->noir->pieces);
            writeHash(fd, hash1);
            writeHash(fd, hash2);
            writeHashTable(fd, jeu->historique);
            close(fd);
            g_string_free(hash1, TRUE);
            g_string_free(hash2, TRUE);
        }
}




void base(GString *file) {
        printf("Utilise le fichier %s comme base de donnée d'ouverture \n", file->str);
}


