#ifndef STRING_HASH_
#define STRING_HASH_
#include "hash_algorithm.h"

class StringHash : public HashAlgorithm {
public:
    StringHash(){};
    ~StringHash(){};

    int     hash(elem_t elem) override ;
    void    free_elem(elem_t elem) override;
    int     elem_equal(elem_t *a, elem_t *b) override;
    elem_t  copy_elem(elem_t elem) override;
    void    show_elem(elem_t elem) override;
private:

};

#endif