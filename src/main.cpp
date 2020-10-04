#include <iostream>
#include "ara/core/result.h"
#include "ara/core/core_error_domain.h"

using namespace ara::core;

Result<uint32_t, ErrorCode> GoodFunc(uint32_t x) {
    return x*5;
} 

Result<uint32_t, ErrorCode> BadFunc(uint32_t x) {
    return Result<uint32_t, ErrorCode>(CoreErrorDomain::Errc::kInvalidArgument);
} 

int main(int, char**) {
    std::cout << "Hello, world!\n";
    Result<uint32_t, ErrorCode> result = GoodFunc(10);
    if(result) {
        std::cout << "Good call: " << *result << std::endl;
    } else {
        std::cout << "Good call: failed";
    }

    result = BadFunc(10);
    if(result) {
        std::cout << "Bad call: " << *result << std::endl;
    } else {
        std::cout << "Bad call: failed with " << result.Error().Message();
    }

}
