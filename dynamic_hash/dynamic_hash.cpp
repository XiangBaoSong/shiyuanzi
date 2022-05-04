#include "dynamic_hash.h"
#include <memory>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MASK(n)  ((1 << (n)) - 1)

DanymicHash::DanymicHash() {
    m_ptr_alg = nullptr;
    m_ptr_hash_table == nullptr;
}

DanymicHash::~DanymicHash() {
    dhash_destroy();
}

dhash_t* DanymicHash::dhash_init(int block_len) {
    int i, size = 1 << INIT_HASH_TABLE_PREFIX;

    dhash_t *dhash = (dhash_t*)malloc(sizeof(dhash_t));
    if (!dhash)
        return NULL;

    memset(dhash, 0, sizeof(dhash_t));
    if (block_len == 0)
        block_len = DEFAULT_BLOCK_LEN;

    dhash->table = (item_t**)malloc(size * sizeof(item_t *));
    if (!dhash->table)
        return NULL;

    for (i = 0; i < size; i++) {
        dhash->table[i] = item_alloc(block_len);
        if (!dhash->table[i])
            return NULL;
        dhash->table[i]->hash_prefix = INIT_HASH_TABLE_PREFIX;
        dhash->table[i]->ref_count = 1;
    }

    dhash->block_len = block_len;
    dhash->hash_prefix = INIT_HASH_TABLE_PREFIX;

    m_ptr_hash_table = dhash;

    return dhash;
}

void DanymicHash::dhash_destroy() {
    int i, j;
    
    int size = 1 << m_ptr_hash_table->hash_prefix;
    block_t *block;

    for (i = 0; i < size; i++) {
        if (m_ptr_hash_table->table[i]->ref_count == 0) {
            block = &m_ptr_hash_table->table[i]->block;
            for (j = 0; j < m_ptr_hash_table->block_len; j++) {
                if (block->data[j])
                    m_ptr_alg->free_elem(block->data[j]);
            }
            free(block->data);
            dhash_destroy_block(m_ptr_hash_table, block->next);
            free(m_ptr_hash_table->table[i]);
        }
    }
    free(m_ptr_hash_table->table);
    free(m_ptr_hash_table);
}

void DanymicHash::set_hash_algorithm(HashAlgorithm* ptr_alg){
    m_ptr_alg = ptr_alg;
}

elem_t* DanymicHash::dhash_query(elem_t elem){
    int slot;

    slot = m_ptr_alg->hash(elem) & MASK(m_ptr_hash_table->hash_prefix);
    return dhash_query_block(m_ptr_hash_table, &m_ptr_hash_table->table[slot]->block, elem);
}

int DanymicHash::dhash_insert(elem_t elem){
    int slot, i, overflow = 1;

    slot = m_ptr_alg->hash(elem) & MASK(m_ptr_hash_table->hash_prefix);
    for (i = 0; i < m_ptr_hash_table->block_len; i++) {
        block_t *block = &m_ptr_hash_table->table[slot]->block;
        if (!block->data[i]) {
            block->data[i] = m_ptr_alg->copy_elem(elem);
            return 0;
        }

        if (m_ptr_alg->hash(elem) != m_ptr_alg->hash(block->data[i]))
            overflow = 0;
    }
    
    if (overflow) {
        return add_overflow_block(m_ptr_hash_table, elem, slot);
    }

    //bucket is full, do bucket division.
    return divide_bucket(m_ptr_hash_table, elem, slot);
}

int DanymicHash::dhash_delete(elem_t elem){
    elem_t* item = dhash_query(elem);

    if (!item)
        return -1;

    m_ptr_alg->free_elem(*item);
    *item = NULL;
    return 0;
}

void DanymicHash::dhash_show(){
    int size = 1 << m_ptr_hash_table->hash_prefix;
    int i;

    for (i = 0; i < size; i++) {
        printf("slot %d: ", i);
        dhash_show_block(m_ptr_hash_table, &m_ptr_hash_table->table[i]->block);
        printf("\n");
    }
}

elem_t* DanymicHash::dhash_query_block(dhash_t *dhash, block_t *block, elem_t elem) {
    while (block) {
        int i;
        for (i = 0; i < dhash->block_len; i++) {
            if (!block->data[i])
                continue;

            if (m_ptr_alg->elem_equal(&block->data[i], &elem))
                return &block->data[i];
        }

        block = block->next;
    }

    return NULL;
}

void DanymicHash::dhash_destroy_block(dhash_t *dhash, block_t *block) {
    block_t *next;
    int i;

    while (block) {
        for (i = 0; i < dhash->block_len; i++) {
            if (block->data[i])
                m_ptr_alg->free_elem(block->data[i]);
        }

        free(block->data);
        next = block->next;
        free(block);
        block = next;
    }
}

item_t* DanymicHash::item_alloc(int block_len) {
    item_t *item = (item_t*)malloc(sizeof(item_t));
    if (!item)
        return NULL;

    memset(item, 0, sizeof(item_t));
    item->block.data = (elem_t *)malloc(block_len * sizeof(elem_t));
    if (!item->block.data)
        return NULL;

    memset(item->block.data, 0, block_len * sizeof(elem_t));
    return item;
}

int DanymicHash::add_overflow_block(dhash_t *dhash, elem_t elem, int slot)
{
    block_t **block = &dhash->table[slot]->block.next;
    while (*block) {
        int i;
        for (i = 0; i < dhash->block_len; i++) {
            if (!(*block)->data[i]) {
                (*block)->data[i] = m_ptr_alg->copy_elem(elem);
                return 0;
            }
        }
        block= &(*block)->next;
    }

    *block = (block_t *)malloc(sizeof(block_t));
    if (!*block)
        return -1;

    memset(*block, 0, sizeof(block_t));
    (*block)->data = (elem_t *)malloc(dhash->block_len * sizeof(elem_t));
    if (!(*block)->data)
        return -1;

    memset((*block)->data, 0, dhash->block_len * sizeof(elem_t));
    (*block)->data[0] = m_ptr_alg->copy_elem(elem);

    return 0;
}


int DanymicHash::divide_bucket(dhash_t *dhash, elem_t elem, int slot) {
    int i, table_size, table_prefix, overflow;
    int new_slot, new_size;
    int num_items, count, middle_slot;
    item_t *top_half, *bottom_half;
    item_t *item, **table;

    while (1) {
        table_prefix = dhash->hash_prefix;
        table_size = 1 << table_prefix;
        if (table_prefix == dhash->table[slot]->hash_prefix) {
            dhash->hash_prefix++;
            new_size = 1 << dhash->hash_prefix;
            table = (item_t **)realloc(dhash->table, new_size * sizeof(item_t *));
            if (!table)
                return -1;

            dhash->table = table;
            for (i = 0; i < table_size; i++) {
                dhash->table[i + table_size] = dhash->table[i];
                dhash->table[i]->ref_count++;
            }
            table_size = new_size;
            slot = m_ptr_alg->hash(elem) & MASK(dhash->hash_prefix);
        }

        num_items = 1 << (dhash->hash_prefix - dhash->table[slot]->hash_prefix);
        count = 0;
        for (i = 0; i < table_size; i++) {
            if (dhash->table[i] ==  dhash->table[slot]) {
                count++;
                if (count == num_items / 2)
                    break;
            }
        }
        middle_slot = i;

        //divide item in slot
        item = item_alloc(dhash->block_len);
        if (!item)
            return -1;
        item->hash_prefix = dhash->table[slot]->hash_prefix;
        item->ref_count = 0;
        if (dhash->table[slot]->block.next) {
            new_slot = m_ptr_alg->hash(dhash->table[slot]->block.data[0]) &
                       MASK(dhash->hash_prefix);
            if (new_slot <= middle_slot) {
                top_half = dhash->table[slot];
                bottom_half = item;
            } else {
                top_half = item;
                bottom_half = dhash->table[slot];
            }
        } else {
            int j = 0;
            top_half = item;
            bottom_half = dhash->table[slot];
            for (i = 0; i < dhash->block_len; i++) {
                new_slot = m_ptr_alg->hash(dhash->table[slot]->block.data[i]) &
                           MASK(dhash->hash_prefix);
                if (new_slot <= middle_slot) {
                    assert(j < dhash->block_len);
                    top_half->block.data[j++] = dhash->table[slot]->block.data[i];
                    dhash->table[slot]->block.data[i] = NULL;
                }
            }
        }

        item = dhash->table[slot];
        top_half->ref_count = 0;
        bottom_half->ref_count = 0;
        for (i = 0; i < table_size; i++) {
            if (dhash->table[i] == item) {
                if (i <= middle_slot) {
                    dhash->table[i] = top_half;
                    top_half->ref_count++;
                } else {
                    dhash->table[i] = bottom_half;
                    bottom_half->ref_count++;
                }
            }
        }
        top_half->hash_prefix++;
        bottom_half->hash_prefix++;

        overflow = 1;
        for (i = 0; i < dhash->block_len; i++) {
            block_t *block = &dhash->table[slot]->block;
            if (!block->data[i]) {
                block->data[i] = m_ptr_alg->copy_elem(elem);
                return 0;
            }
            if (m_ptr_alg->hash(elem) != m_ptr_alg->hash(block->data[i]))
                overflow = 0;
        }
        if (overflow) {
            return add_overflow_block(dhash, elem, slot);
        }
    }

    //can not be reached
    return 0;
}

void DanymicHash::dhash_show_block(dhash_t *dhash, block_t *block) {
    while (block) {
        int i;

        for (i = 0; i < dhash->block_len; i++) {
            if (!block->data[i])
                continue;

            m_ptr_alg->show_elem(block->data[i]);
        }
        block = block->next;
    }
}