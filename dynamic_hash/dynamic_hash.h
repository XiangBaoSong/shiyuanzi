#ifndef DYNAMIC_HASH_
#define DYNAMIC_HASH_

//reference code: https://github.com/xhjcehust/dynamic_hash

#include "data_def.h"
#include "hash_algorithm.h"


class DanymicHash {
public:
    DanymicHash();
    ~DanymicHash();

    dhash_t*    dhash_init(int block_len);
    void        dhash_destroy();
    void        set_hash_algorithm(HashAlgorithm* ptr_alg);
    elem_t*     dhash_query(elem_t elem);
    int         dhash_insert(elem_t elem);
    int         dhash_delete(elem_t elem);
    void        dhash_show();
private:
    dhash_t*        m_ptr_hash_table;
    HashAlgorithm*  m_ptr_alg;

    item_t*     item_alloc(int block_len);
    void        dhash_destroy_block(dhash_t *dhash, block_t *block);
    elem_t*     dhash_query_block(dhash_t *dhash, block_t *block, elem_t elem);
    int         add_overflow_block(dhash_t *dhash, elem_t elem, int slot);
    int         divide_bucket(dhash_t *dhash, elem_t elem, int slot);
    void        dhash_show_block(dhash_t *dhash, block_t *block);
};

#endif