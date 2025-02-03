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

    void* s = List_find(list, String, "Maria");
    if (s != NULL) {
        Data_print(s);
        puts("");
    }

    List_print(list);
    printf("%d\n", List_size(list));
    void* d = List_remove(list, s);

    printf("%d\n", List_size(list));

    List_print(list);

    List_delete(list);

    return EXIT_SUCCESS;
}
