#ifndef HASH_ALGORITHM_FACTORY_
#define HASH_ALGORITHM_FACOTRY_

#include "hash_algorithm.h"
#include "int_hash.h"
#include "string_hash.h"

#include "data_def.h"
#include <memory>

class HashAlgorithmFactory {
public:
    HashAlgorithmFactory() {}
    ~HashAlgorithmFactory() {}

    HashAlgorithm* create_algorithm(E_HASH_ALGORITHM e_alg) noexcept{
        HashAlgorithm* ptr_output = nullptr;

        switch (e_alg)
        {
        case E_STRING_HASH:
            ptr_output = new StringHash();
            break;
        
        case E_INT_HASH :
            ptr_output = new IntHash();
            break;

        default:
            break;
        }

        return ptr_output;
    }

private:

};

#endif