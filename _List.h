#ifndef _LIST_H
#define _LIST_H

#include <stdio.h>

/* ================================================================ */

struct Linked_List_Type {

    size_t size;
    void* (*constructor)(void* self, va_list* app);
    void* (*destructor)(void* self);
    void (*print)(const void* self);
    void* (*insert_first)(void* self, const void* element);
    void* (*remove_first)(void* self);
    void* (*insert_last)(void* self, const void* element);
    void* (*remove_last)(void* self);
    size_t (*get_size)(const void* self);
};

/* ================================================================ */

#endif /* _LIST_H */
