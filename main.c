#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "include/List.h"
#include "include/Types.h"
#include "include/Data_Type.h"

int main(int argc, char** argv) {

    srand(time(0));
    void* list = List_new(List);

    List_insert_first(list, Data_new(String, "Maria"));
    List_insert_first(list, Data_new(String, "Elizabeth"));
    List_insert_first(list, Data_new(String, "Katherine"));

    List_insert_last(list, Data_new(Float, -1.123));

    List_insert_last(list, Data_new(Person, "Jack", 54));

    List_print(list);

    void* data;
    while ((data = List_next(list)) != NULL) {
        Data_print(data);
        puts("");
    }

    puts("");

    while ((data = List_next(list)) != NULL) {
        Data_print(data);
        puts("");
    }

    List_delete(list);

    return EXIT_SUCCESS;
}
