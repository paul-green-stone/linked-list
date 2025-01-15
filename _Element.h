#ifndef __ELEMENT_H
#define __ELEMENT_H

#include <stdio.h>

/* ================================================================ */

struct Element_Type {

    size_t size_in_bytes;

    void* (*constructor)(void* self, va_list* app);
    void* (*destructor)(void* self);
    void (*how_to_print_it)(void* self);
};

/* ================================================================ */

#endif /* __ELEMENT_H */
