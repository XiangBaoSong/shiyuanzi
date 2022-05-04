#include "int_hash.h"
#include <stdlib.h>
#include <stdio.h>

#define  SIZE  128

int IntHash::hash(elem_t elem) {
    return *(int *)elem;
}

void IntHash::free_elem(elem_t elem){
    free(elem);
}

int IntHash::elem_equal(elem_t *a, elem_t *b){
    return (*(int *)a) == (*(int *)b);
}

elem_t IntHash::copy_elem(elem_t elem){
    int *copy = (int *)malloc(sizeof(int));

    *copy = *(int *)elem;
    return copy;
}

void IntHash::show_elem(elem_t elem){
    printf("%d\t", *(int *)elem);
}

