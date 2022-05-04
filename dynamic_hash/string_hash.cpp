#include "string_hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int StringHash::hash(elem_t elem) {
    int result = 0;
    char *str = static_cast<char*>(elem);

    while (*str++) {
        result = result * 31 + *str;
    }
    return result;
}

void StringHash::free_elem(elem_t elem){
    free(elem);
}

int StringHash::elem_equal(elem_t *a, elem_t *b){
    return strcmp((const char *)a, (const char *)b) == 0;
}

elem_t StringHash::copy_elem(elem_t elem){
    char *copy = strdup(static_cast<char*>(elem));
    return copy;
}

void StringHash::show_elem(elem_t elem){
    printf("%s\t", (char *)elem);
}
