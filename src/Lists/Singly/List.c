#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>

#include "../../../include/_List.h"
#include "../../../include/_Data_Type.h"
#include "../../../include/Data_Type.h"

/* ================================================================ */
/* ===== The search operations use these variables as a cache ===== */
/* = to store nodes that may be removed after a successful search = */
/* ================================================================ */

static struct __Node* temporary = NULL;
static struct __Node* before_temporary = NULL;

/* ================================================================ */

/**
 * A singly-linked list node.
 */
struct __Node {

    struct __Node* next;    
    void* data;
};

/* ================================ */

static struct __Node* Node_new(void* data) {

    struct __Node* node = NULL;

    if ((node = calloc(1, sizeof(struct __Node))) == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

/* ================================================================ */
/* ================== SINGLY-LINKED LIST METHODS ================== */
/* ================================================================ */

/* A singly-linked list */
struct __List {

    const void* vtable;
    struct __Node* next;

    /* Number of elements in the list */
    size_t count;

    struct __Node* head;
    struct __Node* tail;
};

/* ================================ */

/**
 * A singly linked list constructor
 */
static void* ctor(void* _self, va_list* app) {

    return _self;
}

/* ================================ */

/**
 * A functiong for getting the number of elements in the list
 */
static ssize_t get_size(const void* _self) {

    const struct __List* self = _self;

    return self->count;
}

/* ================================ */

/**
 * A function for deleting elements from the beginning
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
            self->next = NULL;
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
 * A singly-linked list destructor
 */
static void* dtor(void* _self) {

    struct __List* self = _self;
    void* element = NULL;

    while (self->count > 0) {
        element = remove_first(_self);
        Data_delete(element);
    }

    return _self;
}

/* ================================ */

/**
 * A function for inserting elements at the beginning
 */
static void* insert_first(void* _self, const void* _element) {

    struct __List* self = _self;
    struct __Node* node = Node_new((void*) _element);

    if (self->count == 0) {
        self->head = self->tail = node;
        self->next = self->head;
    }
    else {
        node->next = self->head;
        self->head = node;
    }

    self->count++;

    return (void*) _element;
}

/* ================================ */

/**
 * A function for displaying data contained in the list
 */
static void print(const void* _self) {

    const struct __List* self = _self;
    struct __Node* node;
    size_t i = 0;

    if (self->count == 0) {
        return ;
    }

    for (i = 0, node = self->head; i < self->count; i++, node = node->next) {

        Data_print(node->data);

        if (i + 1 != self->count) {
            printf(" -> ");
        }
    }

    printf("\n");
}

/* ================================ */

/**
 * A function for inserting elements at the end
 */
static void* insert_last(void* _self, const void* element) {

    struct __List* self = _self;
    struct __Node* node = Node_new((void*) element);

    if (self->count == 0) {
        self->head = self->tail = node;
        self->next = self->head;
    }
    else {
        self->tail->next = node;
        self->tail = node;
    }

    self->count++;

    return (void*) element;
}

/* ================================ */

/**
 * A function for deleting elements from the end
 */
static void* remove_last(void* _self) {

    struct __List* self = _self;
    struct __Node* node = NULL;
    void* element = NULL;

    if (self->count > 0) {

        node = self->head;
        element = self->tail->data;

        if (self->count == 1) {
            self->head = self->tail = NULL;
            self->next = NULL;
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

/**
 * A function for searching data in the list
 */
static void* find(const void* _self, const void* type, va_list* app) {

    const struct __List* self = _self;
    struct __Node* node = NULL;

    size_t i = 0;

    va_list app_copy;

    if (self->count > 0) {

        for (temporary = node = self->head; i < self->count || node != NULL; i++, temporary = node = node->next) {

            if ((*(const struct Data_Type**) node->data) == type) {

                #ifdef va_copy
                    va_list ap;
                    va_copy(ap, *app);
                #else
                    va_list ap = *app;
                #endif

                if ((*(const struct Data_Type**) node->data)->compare(node->data, &ap) == 0) {
                    return node->data;
                }
            }

            before_temporary = temporary;
        }

        va_end(app_copy);
    }

    return NULL;
}

/* ================================ */

/**
 * A singly-linked list function for removing the given element from the list
 * (if it exists in the list)
 */
static void* remove_element(void* _self, void* _data) {

    struct __List* self = _self;
    struct __Node* current = NULL;
    struct __Node* previous = NULL;
    void* data = NULL;

    size_t i = 0;

    if (self->count > 0) {

        if (_data == self->head->data) {
            return remove_first(_self);
        }
        else if (_data == self->tail->data) {
            return remove_last(_self);
        }
        /* Delete the element that has just been found */
        else if (temporary->data == _data) {

            before_temporary->next = temporary->next;
            /* Data stored in the node */
            data = temporary->data;

            free(temporary);
        }
        else {
            for (previous = self->head, current = previous->next; current->data != _data || i < self->count; i++, previous = current, current = current->next) ;

            if (current == NULL) {
                return NULL;
            }

            before_temporary->next = current->next;
            data = current->data;
            free(current);
        }

        self->count--;
    }

    return data;
}

/* ================================ */

static void* get_next(void* _self) {

    struct __List* self = _self;
    void* data = NULL;

    data = (self->next != NULL) ? self->next->data : NULL;

    if (data != NULL) {
        self->next = self->next->next;
    } else {
        self->next = self->head;
    }

    return data;
} 

/* ================================================================ */
/* ======================== INITIALIZATION ======================== */
/* ================================================================ */

const struct Linked_List_Type _List = {

    .size = sizeof(struct __List),
    .constructor = ctor,
    .destructor = dtor,
    .print = print,
    .insert_first = insert_first,
    .remove_first = remove_first,
    .get_size = get_size,
    .insert_last = insert_last,
    .remove_last = remove_last,
    .find = find,
    .remove_element = remove_element,
    .get_next = get_next,
};

const void* List = &_List;

/* ================================================================ */
