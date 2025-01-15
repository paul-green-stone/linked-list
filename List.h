#ifndef _LINKED_LIST_ADT_H
#define _LINKED_LIST_ADT_H

/* ================================================================ */

/* A singly-linked list ADT */
extern const void* List;

/* ================================================================ */
/* ========================== INTERFACE =========================== */
/* ================================================================ */

void* List_new(const void* list, ...);

void List_delete(void* list);

void List_print(const void* list);

void* List_insert_first(void* list, const void* element);

void* List_remove_first(void* list);

void* List_insert_last(void* list, const void* element);

size_t List_size(const void* list);

/* ================================================================ */

#endif /* _LINKED_LIST_ADT_H */
