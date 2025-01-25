#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_Data_Type.h"

/* ================================================================ */

struct __Person {

    /* struct Data_Type */
    void* data_type;

    char* first_name;
    unsigned int age;
};

/* ================================ */

static void* _Person_constructor(void* _self, va_list* app) {

    struct __Person* self = _self;

    char* first_name = va_arg(*app, char*);
    unsigned int age = va_arg(*app, unsigned int);

    if ((self->first_name = malloc(sizeof(char) * 32)) == NULL) {
        return NULL;
    }

    strncpy(self->first_name, first_name, 32);
    self->first_name[strlen(self->first_name)] = '\0';

    self->age = age;

    return self;
}

/* ================================ */

static void* _Person_destructor(void* _self) {

    struct __Person* self = _self;

    free(self->first_name);
    self->first_name = NULL;

    return self;
}

/* ================================ */

static void _Person_print(const void* _self) {

    const struct __Person* self = _self;

    printf("%s, %u", self->first_name, self->age);
}

/* ================================ */

static int _Person_compare(const void* _self, va_list* app) {

    const struct __Person* self = _self;

    char* first_name = va_arg(*app, char*);
    unsigned int age = va_arg(*app, unsigned int);

    return !((strcmp(self->first_name, first_name) == 0) && (self->age == age));
}

/* ================================ */

static struct Data_Type _Person = {
    .size_in_bytes = sizeof(struct __Person),
    .constructor = _Person_constructor,
    .destructor = _Person_destructor,
    .how_to_print_it = _Person_print,
    .compare = _Person_compare,
};

const void* Person = &_Person;

/* ================================================================ */
