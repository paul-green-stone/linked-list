#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "List.h"
#include "Element.h"

#define SIZE 1000

int main(int argc, char** argv) {

    srand(time(0));
    void* list = List_new(List);

    for (size_t i = 0; i < SIZE; i++) {
        List_insert_first(list, Element_new(Integer, rand() % 1000000));
    }

    List_print(list);

    List_delete(list);

    return EXIT_SUCCESS;
}
