#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "../../include/_Data_Type.h"

/* ================================================================ */
/* ======================== IMPLEMENTATION ======================== */
/* ================================================================ */

void* Data_new(const void* _dt, ...) {

    const struct Data_Type* dt = _dt;
    void* elm = NULL;

    if ((elm = calloc(1, dt->size_in_bytes)) == NULL) {
        return NULL;
    }

    *(const struct Data_Type**) elm = dt;

    if (dt->constructor != NULL) {

        va_list ap;

        va_start(ap, _dt);
        elm = dt->constructor(elm, &ap);
        va_end(ap);
    }

    return elm;
}

/* ================================ */

void Data_delete(void* dt) {

    const struct Data_Type** element_type_ptr = dt;

    if ((dt != NULL) && (*element_type_ptr != NULL) && ((*element_type_ptr)->destructor != NULL)) {
        dt = (*element_type_ptr)->destructor(dt);
    }

    free(dt);
}

/* ================================ */

void Data_print(const void* dt) {

    struct Data_Type** element_type_ptr = (void*) dt;

    if ((dt != NULL) && (*element_type_ptr != NULL) && ((*element_type_ptr)->how_to_print_it != NULL)) {
        (*element_type_ptr)->how_to_print_it(dt);
    }
}

/* ================================================================ */
