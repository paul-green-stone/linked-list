#include <stddef.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "Element.h"
#include "List.h"
#include "_List.h"

/* ================================================================ */

struct __Node {

    struct __Node* next;
    void* data;
};

struct __List {

    const void* vtable;

    /* Number of elements in the list */
    size_t count;

    struct __Node* head;
    struct __Node* tail;
};

/* ================================================================ */
/* ======================== IMPLEMENTATION ======================== */
/* ================================================================ */

static struct __Node* _Node_new(void* data) {

    struct __Node* n = calloc(1, sizeof(struct __Node));

    n->data = data;

    return n;
}

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

void List_delete(void* list) {

    const struct Linked_List_Type** list_ptr = list;

    if ((list != NULL) && (*list_ptr != NULL) && ((*list_ptr)->destructor != NULL)) {
        list = (*list_ptr)->destructor(list);
    }

    free(list);
}

size_t List_size(const void* _list) {

    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->get_size != NULL)) {
        return (*list)->get_size(_list);
    }
}

void* List_insert_first(void* _list, const void* _element) {

    const struct Linked_List_Type* const* list = _list;
    const struct Element_Type* const* element_type_ptr = _element;

    char d = (*(struct Element_Type**) element_type_ptr == String) || (*(struct Element_Type**) element_type_ptr == Integer) || (*(struct Element_Type**) element_type_ptr == Float);

    if (!d) {
        return NULL;
    }

    if ((_list != NULL) && (*list != NULL) && ((*list)->insert_first != NULL)) {
        return (*list)->insert_first(_list, _element);
    }

    return NULL;
}

void* List_remove_first(void* _list) {
    
    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->remove_first != NULL)) {
        return (*list)->remove_first(_list);
    }

    return NULL;
}

void List_print(const void* _list) {

    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->print != NULL)) {
        return (*list)->print(_list);
    }
}

void* List_insert_last(void* _list, const void* _element) {

    const struct Linked_List_Type* const* list = _list;
    const struct Element_Type* const* element_type_ptr = _element;

    char d = (*(struct Element_Type**) element_type_ptr == String) || (*(struct Element_Type**) element_type_ptr == Integer) || (*(struct Element_Type**) element_type_ptr == Float);

    if (!d) {
        return NULL;
    }

    if ((_list != NULL) && (*list != NULL) && ((*list)->insert_first != NULL)) {
        return (*list)->insert_last(_list, _element);
    }

    return NULL;
}

void* List_remove_last(void* _list) {
    
    const struct Linked_List_Type* const* list = _list;

    if ((_list != NULL) && (*list != NULL) && ((*list)->remove_last != NULL)) {
        return (*list)->remove_last(_list);
    }

    return NULL;
}

/* ================================================================ */
/* ============================ STATIC ============================ */
/* ================================================================ */

/**
 * The `get_size` implementation for a singly-linked list
 */
static size_t get_size(const void* _self) {

    const struct __List* self = _self;

    return self->count;
}

/* ================================ */

/**
 * The `remove_first` implementation for a singly-linked list
 */
void* remove_first(void* _self) {
    
    struct __List* self = _self;
    struct __Node* node = NULL;
    void* element = NULL;

    if (self->count > 0) {

        node = self->head;
        element = node->data;

        if (self->count == 1) {
            self->head = self->tail = NULL;
        }
        else {
            self->head = node->next;
        }

        self->count--;
        free(node);
    }

    return element;
}

/* ================================ */

/**
 * The `destructor` implementation for a singly-linked list
 */
static void* destructor(void* _self) {

    struct __List* self = _self;
    void* element = NULL;

    while (self->count > 0) {
        element = remove_first(_self);
        Element_delete(element);
    }

    return _self;
}

/* ================================ */

/**
 * The `insert_first` implementation for a singly-linked list
 */
void* insert_first(void* _self, const void* _element) {

    struct __List* self = _self;
    struct __Node* node = _Node_new(_element);

    if (self->count == 0) {
        self->head = self->tail = node;
    }
    else {
        node->next = self->head;
        self->head = node;
    }

    self->count++;

    return _element;
}

/* ================================ */

/**
 * The 'print` implementation for a singly-linked list
 */
void print(const void* _self) {

    const struct __List* self = _self;
    struct __Node* node;
    size_t i = 0;

    if (self->count == 0) {
        return ;
    }

    for (i = 0, node = self->head; i < self->count; i++, node = node->next) {

        Element_print(node->data);

        if (i + 1 != self->count) {
            printf(" -> ");
        }
    }

    printf("\n");
}

/* ================================ */

/**
 * The `insert_last` implementation for a singly-linked list
 */
void* insert_last(void* _self, const void* element) {

    struct __List* self = _self;
    struct __Node* node = _Node_new(element);

    if (self->count == 0) {
        self->head = self->tail = node;
    }
    else {
        self->tail->next = node;
        self->tail = node;
    }

    self->count++;

    return element;
}

/* ================================ */

/**
 * The `remove_last` implementation for a singly-linked list
 */
void* remove_last(void* _self) {

    struct __List* self = _self;
    struct __Node* node = NULL;
    void* element = NULL;

    if (self->count > 0) {

        node = self->head;
        element = self->tail->data;

        if (self->count == 1) {
            self->head = self->tail = NULL;
        }
        else {
            while (node->next != self->tail) node = node->next;

            self->tail = node;
        }

        self->count--;

        free(node->next);
        node->next = NULL;
    }

    return element;
}

/* ================================================================ */

const struct Linked_List_Type _List = {
    .size = sizeof(struct __List),
    .constructor = NULL,
    .destructor = destructor,
    .print = print,
    .insert_first = insert_first,
    .remove_first = remove_first,
    .get_size = get_size,
    .insert_last = insert_last,
    .remove_last = remove_last,
};

const void* List = &_List;
