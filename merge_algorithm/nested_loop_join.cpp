#include "nested_loop_join.h"
#include <assert.h>

st_table NestedLoopJoin::join(const st_table& t1, const st_table& t2, const int join_idx) {
    assert (t1.size() > join_idx && t2.size() > join_idx);

    st_table output_table{};

    for (auto t1_row : t1) {
        for (auto t2_row: t2) {
            if (t1_row[join_idx] == t2_row[join_idx]) {
                t1_row.insert(t1_row.end(), t2_row.begin(), t2_row.end());

                output_table.push_back(t1_row);
            }
        }
    }

    return output_table;
}