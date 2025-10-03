#include <iostream>
#include "value.hpp"
#include "integer.hpp"

using namespace tkg;

int main()
{
    StoredType<int> x;
    Value a = 4294967299;
    Value b = "Vasya Petrov";
    Value c = true;
    Value d = NIL;
    Value e = None;
    std::cout << a << '\n';
    std::cout << b << '\n';
    std::cout << c << '\n';
    std::cout << d << '\n';
    std::cout << e << '\n';

    Value f = cons(nullptr, cons(12345, "Hello, world!"));
    std::cout << f << '\n';
    return 0;
}