#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "_Data_Type.h"

#define THRESHOLD 1e-4f

/* ================================================================ */

struct __Float {

    /* struct Data_Type */
    const void* element_type;

    float data;
};

/* ================================ */

static void* _Float_constructor(void* _self, va_list* app) {

    struct __Float* self = _self;
    const float data = va_arg(*app, const double);

    self->data = data;

    return self;
}

/* ================================ */

static void _Float_print(const void* _self) {

    const struct __Float* self = _self;

    printf("%.2f", self->data);
}

/* ================================ */

static int _Float_compare(const void* _self, va_list* app) {

    const struct __Float* self = _self;
    float f = va_arg(*app, double);

    return !((fabs(self->data - f)) < THRESHOLD);
}

/* ================================ */

static struct Data_Type _Float = {
    .size_in_bytes = sizeof(struct __Float),
    .constructor = _Float_constructor,
    .destructor = NULL,
    .how_to_print_it = _Float_print,
    .compare = _Float_compare,
};

const void* Float = &_Float;

/* ================================================================ */
