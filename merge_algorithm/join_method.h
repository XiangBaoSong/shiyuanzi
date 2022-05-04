#ifndef JOIN_METHOD_
#define JOIN_METHOD_

#include<string>
#include<vector>
#include "data_def.h"

class JoinMethod {
public:
    JoinMethod(){};
    virtual ~JoinMethod(){};

    virtual st_table join(const st_table& t1, const st_table& t2, const int join_idx) = 0;
protected:

private:

};



#endif
