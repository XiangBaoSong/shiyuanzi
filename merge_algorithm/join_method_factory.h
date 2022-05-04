#ifndef JOIN_METHOD_FACTORY_
#define JOIN_METHOD_FACTORY_

#include "hash_join.h"
#include "nested_loop_join.h"
#include "sort_merge_join.h"
#include <memory>

class JoinMethodFactory {
public:
    virtual std::shared_ptr<JoinMethod> create_method(E_JOIN_METHOD e_method) noexcept {
        std::shared_ptr<JoinMethod> ptr_method = nullptr;

        switch (e_method)
        {
        case E_HASH:
            ptr_method = std::make_shared<HashJoin>();
            break;
        case E_NESTED_LOOP:
            ptr_method = std::make_shared<NestedLoopJoin>();
            break;
        case E_SORT_MERGE:
            ptr_method = std::make_shared<SortMergeJoin>();
            break;
        default:
            break;
        }

        return ptr_method;
    }

private:

};

#endif