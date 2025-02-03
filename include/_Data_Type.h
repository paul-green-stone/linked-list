#ifndef __DATA_TYPE_REPRESENTATION_H
#define __DATA_TYPE_REPRESENTATION_H

#include <stdio.h>
#include <stdarg.h>

/* ================================================================ */

struct Data_Type {

    size_t size_in_bytes;

    void* (*constructor)(void* self, va_list* app);
    void* (*destructor)(void* self);
    void (*how_to_print_it)(const void* self);
    int (*compare)(const void* self, va_list* app);
};

/* ================================================================ */

#endif /* __DATA_TYPE_REPRESENTATION_H */
