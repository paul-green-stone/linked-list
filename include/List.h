#ifndef _LINKED_LIST_INTERFACE_H
#define _LINKED_LIST_INTERFACE_H

#include <sys/types.h>

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

/**
 * The function creates a new instance of a linked list of type `list`.
 */
void* List_new(const void* list, ...);

/* ================================ */

/**
 * The function destroys the given list (and all its elements) and reclaims the memory occupied by it.
 */
void List_delete(void* list);

/* ================================ */

/** 
 * Outputs the content of the given list.
*/
void List_print(const void* list);

/* ================================ */

/**
 * The function inserts a new element at the beginning of the list.
 */
void* List_insert_first(void* list, const void* element);

/* ================================ */

/**
 * The function removes the element from the list returning the element itself.
 * To destroy the element, call `Element_destroy` on it.
 */
void* List_remove_first(void* list);

/* ================================ */

/**
 * The function inserts a new element at the end of the list.
 */
void* List_insert_last(void* list, const void* element);

/* ================================ */

/**
 * The functions returns the number of elements in the list.
 */
ssize_t List_size(const void* list);

/* ================================ */

/**
 * The function searches for the specified data type and value in the given list.
 */
void* List_find(const void* list, const void* type, ...);

/* ================================ */

/**
 * The function for removing the given element from the list
 */
void* List_remove(void* list, void* data);

/* ================================================================ */

#endif /* _LINKED_LIST_INTERFACE_H */
