#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../../include/_List.h"
#include "../../include/_Data_Type.h"
#include "../../include/Types.h"
#include "../../include/Data_Type.h"

/* ================================================================ */

/**
 * A singly-linked list node.
 */
struct __Node {

    struct __Node* next;
    void* data;
};

/* ================================ */

void* List_new(const void* _list, ...) {

    const struct Linked_List_Type* list = _list;
    void* l = NULL;

    if ((l = calloc(1, list->size)) == NULL) {
        return NULL;
    }

    *(const struct Linked_List_Type**) l = list;

    if (list->constructor != NULL) {

        va_list ap;

        va_start(ap, _list);
        l = list->constructor(l, &ap);
        va_end(ap);
    }

    return l;
}

/* ================================ */

void List_delete(void* list) {

    const struct Linked_List_Type** list_ptr = list;

    if ((list != NULL) && (*list_ptr != NULL) && ((*list_ptr)->destructor != NULL)) {
        list = (*list_ptr)->destructor(list);
    }

    free(list);
}

/* ================================ */

ssize_t List_size(const void* _list) {

    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->get_size != NULL)) {
        return (*list)->get_size(_list);
    }

    return -1;
}

/* ================================ */

void* List_insert_first(void* _list, const void* _element) {

    const struct Linked_List_Type* const* list = _list;
    const struct Data_Type* const* element_type_ptr = _element;

    if ((_list != NULL) && (*list != NULL) && ((*list)->insert_first != NULL)) {
        return (*list)->insert_first(_list, _element);
    }

    return NULL;
}

/* ================================ */

void* List_remove_first(void* _list) {
    
    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->remove_first != NULL)) {
        return (*list)->remove_first(_list);
    }

    return NULL;
}

/* ================================ */

void List_print(const void* _list) {

    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->print != NULL)) {
        (*list)->print(_list);
    }
}

/* ================================ */

void* List_insert_last(void* _list, const void* _element) {

    const struct Linked_List_Type* const* list = _list;
    const struct Data_Type* const* element_type_ptr = _element;

    if ((_list != NULL) && (*list != NULL) && ((*list)->insert_first != NULL)) {
        return (*list)->insert_last(_list, _element);
    }

    return NULL;
}

/* ================================ */

void* List_remove_last(void* _list) {
    
    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->remove_last != NULL)) {
        return (*list)->remove_last(_list);
    }

    return NULL;
}

/* ================================ */

void* List_find(const void* _list, const void* type, ...) {
    
    const struct Linked_List_Type* const* list = _list;
    void* result = NULL;

    if ((_list != NULL) && (*list != NULL) && ((*list)->find != NULL)) {
        
        va_list ap;
        va_start(ap, type);

        result = (*list)->find(_list, type, &ap);

        va_end(ap);
    }

    return result;
}

/* ================================ */

void* List_remove(void* _list, void* _data) {

    struct Linked_List_Type** list = _list;
    void* data = NULL;

    if ((_list != NULL) && (*list != NULL) && ((*list)->remove_element != NULL)) {
    
        data = (*list)->remove_element(_list, _data);
        Data_delete(data);
    }

    return data;
}

/* ================================ */

void* List_next(const void* _list) {
    
    struct Linked_List_Type** list = (void*) _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->get_next != NULL)) {
        
        return (*list)->get_next((void*) _list);
    }

    return NULL;
}

/* ================================================================ */

