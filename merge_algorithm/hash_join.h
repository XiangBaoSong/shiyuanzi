#ifndef HASH_JOIN_
#define HAHS_JOIN_

#include "join_method.h"
#include <unordered_map>
#include <memory>
#include <string>

class HashJoin : public JoinMethod {
public:
    HashJoin(){};
    ~HashJoin(){};

    st_table join(const st_table& t1, const st_table& t2, const int join_idx) override;
private:
    std::unordered_map<std::string, st_row_data> create_hash_table(const st_table* t, const int key_idx);

};

#endif