#ifndef DATA_DEF_
#define DATA_DEF_

#include<string>
#include<vector>

using st_row_data = std::vector<std::string>;
using st_table = std::vector<st_row_data>;

enum E_JOIN_METHOD {
    E_HASH = 1,
    E_SORT_MERGE = 2,
    E_NESTED_LOOP = 3
};

#endif