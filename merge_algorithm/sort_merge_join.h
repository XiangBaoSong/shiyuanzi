#ifndef SORT_MERGE_JOIN_
#define SORT_MERGE_JOIN_

#include "join_method.h"

class SortMergeJoin : public JoinMethod {
public:
    SortMergeJoin(){};
    ~SortMergeJoin(){};

    st_table join(const st_table& t1, const st_table& t2, const int join_idx) override;
private:
    st_table sort_table(const st_table& t, const int join_idx);
    st_table merge_table(const st_table& t1, const st_table& t2, const int join_idx);
};

#endif