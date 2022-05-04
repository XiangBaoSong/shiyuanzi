#ifndef HASH_ALGORITHM_
#define HASH_ALGORITHM_

#include "data_def.h"

class HashAlgorithm {
public:
    virtual int hash(elem_t elem) = 0 ;
    virtual void free_elem(elem_t elem) = 0;
    virtual int elem_equal(elem_t *a, elem_t *b) = 0;
    virtual elem_t copy_elem(elem_t elem) = 0;
    virtual void show_elem(elem_t elem) = 0;
private:

};

#endif