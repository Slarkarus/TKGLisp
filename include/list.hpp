#ifndef TKG_TYPES_HPP
#define TKG_TYPES_HPP

namespace tkg
{
    class Value;

    struct List
    {
        Value *a;
        Value *b;

        List() {}
    };

    Value cons(Value a, Value b);

    Value car(Value a);

    Value cdr(Value a);

    bool isList(Value a);
}

#endif // TKG_TYPES_HPP