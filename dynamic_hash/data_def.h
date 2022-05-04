#ifndef DATA_DEF_
#define DATA_DEF_

#define DEFAULT_BLOCK_LEN 4
#define INIT_HASH_TABLE_PREFIX 0

typedef void * elem_t;
typedef struct block_s block_t;

struct block_s {
    elem_t* data;
    block_t *next; //overflow block
};

typedef struct {
    int ref_count;
    int hash_prefix;
    block_t block;
} item_t;

typedef struct {
    item_t **table;
    int block_len;
    int hash_prefix; //start from 1 and hash table size is 1 << (hash_prefix - 1)
} dhash_t;

enum E_HASH_ALGORITHM {
    E_STRING_HASH = 1,
    E_INT_HASH = 2,
};

#endif