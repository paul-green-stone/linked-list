#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include "_List.h"
#include "../Types/_Data_Type.h"

/* ================================================================ */

/**
 * A singly-linked list node.
 */
static struct __Node {

    struct __Node* next;    
    void* data;
};

static struct __Node* Node_new(void* data) {

    struct __Node* node = NULL;

    if ((node = calloc(1, sizeof(struct __Node))) == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

/* ================================ */

/* A singly-linked list */
struct __List {

    const void* vtable;

    /* Number of elements in the list */
    size_t count;

    struct __Node* head;
    struct __Node* tail;
};

/* ================================ */

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
static void* remove_first(void* _self) {
    
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
    struct __Node* node = Node_new(_element);

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
    struct __Node* node = Node_new(element);

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

/* ================================ */

void* find(const void* _self, const void* type, va_list* app) {

    struct __List* self = _self;
    struct __Node* node = NULL;

    size_t i = 0;

    va_list app_copy;

    if (self->count > 0) {

        for (node = self->head; i < self->count || node != NULL; i++, node = node->next) {

            if ((*(const struct Data_Type**) node->data) == type) {

                va_copy(&app_copy, *app);

                if ((*(const struct Data_Type**) node->data)->compare(node->data, &app_copy) == 0) {
                    return node->data;
                }
            }
        }

        va_end(app_copy);
    }

    return NULL;
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
    .find = find,
};

const void* List = &_List;

/* ================================================================ */
