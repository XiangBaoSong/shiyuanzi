#ifndef NESTED_LOOP_JOIN_
#define NESTED_LOOP_JOIN_

#include "join_method.h"

class NestedLoopJoin : public JoinMethod {
public:
    NestedLoopJoin(){};
    ~NestedLoopJoin(){};

    st_table join(const st_table& t1, const st_table& t2, const int join_idx) override;
private:


};

#endif