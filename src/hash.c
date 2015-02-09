/**
 * @copyright
 * @author BOUTES Paul, CASSAN Damien, DRUELLE Mathias
 * @brief Fichier gérant les hashs, c'est à dire l'écriture, la lecture
 */

#include "./hash.h"

void pieceToHash(gpointer data, gpointer userData) {
    GString* hash;
    Piece *piece;
    char colonne;
    char ligne;
    hash = (GString*) userData;
    piece = (Piece*)data;
    colonne = (char) (piece->casePiece->colonne + 'a');
    ligne = (char) (piece->casePiece->ligne + '1');
    hash = g_string_append_c(hash, piece->type);
    hash = g_string_append_c(hash, colonne);
    hash = g_string_append_c(hash, ligne);
} 

GString* createHash(GList *pieces) {
    GString *hash = g_string_new("");
    g_list_foreach(pieces, pieceToHash, hash);
    return hash;
}
