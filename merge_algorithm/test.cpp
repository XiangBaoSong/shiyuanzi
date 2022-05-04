#include "join_method_factory.h"
#include <memory>

int main(int argc, char** argv[]) {

    std::shared_ptr<JoinMethodFactory> ptr_factory = std::make_shared<JoinMethodFactory>();

    std::shared_ptr<JoinMethod> ptr_method = ptr_factory->create_method(E_HASH);

    st_table t1, t2;
    
    st_table join_result = ptr_method->join(t1, t2, 2);

    return 0;
}