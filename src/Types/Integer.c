#include <stdio.h>
#include <stdlib.h>

#include "_Data_Type.h"

/* ================================================================ */

struct __Integer {

    /* struct Element_Type */
    const void* element_type;

    int data;
};

/* ================================ */

static void* _Integer_constructor(void* _self, va_list* app) {

    struct __Integer* self = _self;
    const int data = va_arg(*app, const int);

    self->data = data;

    return self;
}

/* ================================ */

static void _Integer_print(const void* _self) {

    const struct __Integer* self = _self;

    printf("%d", self->data);
}

/* ================================ */

static int _Integer_compare(const void* _self, va_list* app) {

    const struct __Integer* self = _self;
    int integer = va_arg(*app, int);

    return (self->data - integer);
}

/* ================================ */

static struct Data_Type _Integer = {
    .size_in_bytes = sizeof(struct __Integer),
    .constructor = _Integer_constructor,
    .destructor = NULL,
    .how_to_print_it = _Integer_print,
    .compare = _Integer_compare,
};

const void* Integer = &_Integer;

/* ================================================================ */
