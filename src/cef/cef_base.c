/**
* @copyright
* @file cef_base.c
* @author Boutes Paul, Cassan Damien
* @brief Contient les fonctions relative a la gestion de la memoire de chromium
*/

#include "./cef_base.h"



int addRef(cef_base_t *self) {
    return 0;
}

int release(cef_base_t* self) {
    return 0;
}


int getRefct(cef_base_t *self) {
    return 0;
}

void initializeCefBase(cef_base_t *base) {
    base->add_ref = addRef;
    base->release = release;
    base->get_refct = getRefct;
}
