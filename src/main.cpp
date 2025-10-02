#include <iostream>
#include "types.hpp"
#include "integer.hpp"

using namespace tkg;

int main(){
    std::cout << sizeof(std::string*) << '\n';
    std::cout << sizeof(tkg::Integer*) << '\n';
    std::cout << sizeof(tkg::LispValueData) << '\n';
    std::cout << sizeof(tkg::LispValueType) << '\n';
    std::cout << sizeof(tkg::LispValue) << '\n';
    std::cout << sizeof(tkg::ConsList) << '\n';
    std::cout << sizeof(tkg::ConsList*) << '\n';

    return 0;
}