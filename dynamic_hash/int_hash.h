#ifndef INT_HASH_
#define INT_HASH_
#include "data_def.h"
#include "hash_algorithm.h"

class IntHash : public HashAlgorithm {
public:
    IntHash(){}
    ~IntHash(){}

    int     hash(elem_t elem) override ;
    void    free_elem(elem_t elem) override;
    int     elem_equal(elem_t *a, elem_t *b) override;
    elem_t  copy_elem(elem_t elem) override;
    void    show_elem(elem_t elem) override;
private:

};

#endif