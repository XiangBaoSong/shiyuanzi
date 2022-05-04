#include "hash_join.h"
#include <unordered_map>
#include <assert.h>

st_table HashJoin::join(const st_table& t1, const st_table& t2, const int join_idx) {
    assert (t1.size() > join_idx && t2.size() > join_idx);

    //select hash data
    const st_table* ptr_table_small = &t1;
    const st_table* ptr_table_big = &t2;
    if (t2.size() < t1.size()) {
        ptr_table_small = &t2;
        ptr_table_big = &t1;
    }

    //create hash table
    auto hash_table = create_hash_table(ptr_table_small, join_idx);

    //merge
    st_table t3;
    for (auto row1 : *ptr_table_big) {
        std::string join_key = row1[join_idx];
        
        if (hash_table.find(join_key) != hash_table.end()) {
            st_row_data& row2 = hash_table[join_key];
            row1.insert(row1.end(), row2.begin(), row2.end()) ;

            t3.push_back(row1);
        }
    }

    return t3;
}

std::unordered_map<std::string, st_row_data> HashJoin::create_hash_table(const st_table* t, const int key_idx) {
    assert (t != nullptr);

    std::unordered_map<std::string, st_row_data> hash_map;

    for (st_row_data row : *t) {
        hash_map[row[key_idx]] = row;
    }

    return hash_map;
}