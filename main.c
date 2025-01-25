#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "List.h"
#include "src/Types.h"
#include "src/Data_Type.h"

#define SIZE 1000

int main(int argc, char** argv) {

    srand(time(0));
    void* list = List_new(List);

    // for (size_t i = 0; i < SIZE; i++) {
    //     List_insert_first(list, Element_new(Integer, rand() % 1000000));
    // }

    List_insert_first(list, Data_new(String, "Maria"));
    List_insert_first(list, Data_new(String, "Elizabeth"));
    List_insert_first(list, Data_new(String, "Katherine"));

    void* s = List_find(list, String, "Elizabeth");

    if (s != NULL) {
        Data_print(s);
        puts("");
    }

    s = List_find(list, String, "Maria");
    if (s != NULL) {
        Data_print(s);
        puts("");
    }

    List_insert_last(list, Data_new(Float, -1.123));

    s = List_find(list, Float, -1.12300003);
    if (s != NULL) {
        Data_print(s);
        puts("");
    }

    List_insert_last(list, Data_new(Person, "Jack", 54));

    s = List_find(list, Person, "Jack", 54);
    if (s != NULL) {
        Data_print(s);
        puts("");
    }

    List_print(list);

    List_delete(list);

    return EXIT_SUCCESS;
}
