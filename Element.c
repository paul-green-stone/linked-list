#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "_Element.h"
#include "Element.h"

/* ================================================================ */

struct __String {

    /* struct Element_Type */
    const void* element_type;

    char* data;
};

/* ================================ */

struct __Integer {

    /* struct Element_Type */
    const void* element_type;

    int data;
};

/* ================================ */

struct __Float {

    /* struct Element_Type */
    const void* element_type;

    float data;
};

/* ================================================================ */
/* ======================== IMPLEMENTATION ======================== */
/* ================================================================ */

void* Element_new(const void* _element, ...) {

    const struct Element_Type* element = _element;
    void* elm = NULL;

    if ((elm = calloc(1, element->size_in_bytes)) == NULL) {
        return NULL;
    }

    *(const struct Element_Type**) elm = element;

    if (element->constructor != NULL) {

        va_list ap;

        va_start(ap, _element);
        elm = element->constructor(elm, &ap);
        va_end(ap);
    }

    return elm;
}

void Element_delete(void* element) {

    const struct Element_Type** element_type_ptr = element;

    if ((element != NULL) && (*element_type_ptr != NULL) && ((*element_type_ptr)->destructor != NULL)) {
        element = (*element_type_ptr)->destructor(element);
    }

    free(element);
}

void Element_print(const void* element) {

    const struct Element_Type** element_type_ptr = element;

    if ((element != NULL) && (*element_type_ptr != NULL) && ((*element_type_ptr)->how_to_print_it != NULL)) {
        (*element_type_ptr)->how_to_print_it(element);
    }
}

/* ================================================================ */
/* ==================== STRING IMPLEMENTATION ===================== */
/* ================================================================ */

static void* _String_constructor(void* _self, va_list* app) {

    struct __String* self = _self;
    const char* textual_data = va_arg(*app, const char*);

    if ((self->data = malloc(strlen(textual_data) + 1)) == NULL) {
        return NULL;
    }

    strcpy(self->data, textual_data);

    return self;
}

/* ================================ */

static void* _String_destructor(void* _self) {

    struct __String* self = _self;

    free(self->data);
    self->data = NULL;

    return self;
}

/* ================================ */

static void _String_print(void* _self) {

    struct __String* self = _self;

    printf("%s", self->data);
}

/* ================================ */

static struct Element_Type _String = {
    .size_in_bytes = sizeof(struct __String),
    .constructor = _String_constructor,
    .destructor = _String_destructor,
    .how_to_print_it = _String_print,
};

const void* String = &_String;

/* ================================================================ */
/* ==================== INTEGER IMPLEMENTATION ==================== */
/* ================================================================ */

static void* _Integer_constructor(void* _self, va_list* app) {

    struct __Integer* self = _self;
    const int data = va_arg(*app, const int);

    self->data = data;

    return self;
}

/* ================================ */

static void _Integer_print(void* _self) {

    struct __Integer* self = _self;

    printf("%d", self->data);
}

/* ================================ */

static struct Element_Type _Integer = {
    .size_in_bytes = sizeof(struct __Integer),
    .constructor = _Integer_constructor,
    .destructor = NULL,
    .how_to_print_it = _Integer_print,
};

const void* Integer = &_Integer;

/* ================================================================ */
/* ===================== FLOAT IMPLEMENTATION ===================== */
/* ================================================================ */

static void* _Float_constructor(void* _self, va_list* app) {

    struct __Float* self = _self;
    const float data = va_arg(*app, const double);

    self->data = data;

    return self;
}

/* ================================ */

static void _Float_print(void* _self) {

    struct __Float* self = _self;

    printf("%.2f", self->data);
}

/* ================================ */

static struct Element_Type _Float = {
    .size_in_bytes = sizeof(struct __Float),
    .constructor = _Float_constructor,
    .destructor = NULL,
    .how_to_print_it = _Float_print,
};

const void* Float = &_Float;

/* ================================================================ */
