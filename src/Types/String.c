#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_Data_Type.h"

/* ================================================================ */

struct __String {

    /* struct Data_type */
    const void* data_type;

    char* data;
};

/* ================================ */

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

static int _String_compare(const void* _self, va_list* app) {

    struct __String* self = _self;
    const char* string = va_arg(*app, const char*);

    return (strcmp(self->data, string));
}

/* ================================ */

static struct Data_Type _String = {
    .size_in_bytes = sizeof(struct __String),
    .constructor = _String_constructor,
    .destructor = _String_destructor,
    .how_to_print_it = _String_print,
    .compare = _String_compare,
};

const void* String = &_String;

/* ================================================================ */
