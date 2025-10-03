#include <iostream>
#include <vector>
#include "value.hpp"
#include "integer.hpp"

using namespace tkg;

int main()
{
    std::vector<Value> arr;

    arr.push_back(8235235);
    arr.push_back(true);
    arr.push_back("In the town");
    arr.push_back(NIL);
    arr.push_back(None);
    arr.push_back(cons(None, cons(4294967299, cons("Where i was born!", NIL))));
    arr.push_back(cons(NIL, cons("Lived a man", cons("Who sailed to sea", true))));

    for (auto i : arr)
    {
        std::cout << i << '\n';
    }
    return 0;
}