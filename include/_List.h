#ifndef _LINKED_LIST_REPRESENTATION_H
#define _LINKED_LIST_REPRESENTATION_H

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>

/* ================================================================ */

/**
 * A singly linked list data type
 */
struct Linked_List_Type {

    size_t size;
    ssize_t (*get_size)(const void* self);

    /* How to construct the list */
    void* (*constructor)   (void* self, va_list* app);
    /* How to destroy a the list */
    void* (*destructor)    (void* self);
    /* How to insert data at the beginning */
    void* (*insert_first)  (void* self, const void* element);
    /* How to remove data from the beginning  */
    void* (*remove_first)  (void* self);
    /* How to insert data at the end */
    void* (*insert_last)   (void* self, const void* element);
    /* How to remove data from the end */
    void* (*remove_last)   (void* self);
    /* How to find data in the list */
    void* (*find)          (const void* self, const void* type, va_list* app);
    /* How to delete element from the list */
    void* (*remove_element)(void* list, void* data);

    /* How to print the list */
    void (*print)          (const void* self);
};

/* ================================================================ */

#endif /* _LINKED_LIST_REPRESENTATION_H */
