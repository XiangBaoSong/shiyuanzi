#include "hash_algorithm_factory.h"
#include "dynamic_hash.h"
#include <vector>
#include <string>
#include <stdio.h>

static  std::string generate_random_string()
{
    int i, len = rand() % 32;
    std::string str;

    for (i = 0; i < len; i++) {
        char ch = 'a' + rand() % ('z' - 'a');
        str += ch;
    }

    return str;
}

int main(int argc, char* argv[]) {
    DanymicHash dhash;
    HashAlgorithmFactory algorithm_factory;

    HashAlgorithm* ptr_algorithm = algorithm_factory.create_algorithm(E_STRING_HASH);
    if (nullptr == ptr_algorithm) {
        return -1;
    }

    dhash.set_hash_algorithm(ptr_algorithm);

    std::vector<std::string> test_data; 
    for (int idx = 0; idx < 100; idx ++) {
        test_data.push_back(generate_random_string());
    }

    for (int idx = 0; idx < 100; idx ++) {
        auto item = test_data[idx];

        dhash.dhash_query((char*)item.c_str());

        dhash.dhash_delete((char*)item.c_str());
    }

    dhash.dhash_destroy();

    return 0;
}