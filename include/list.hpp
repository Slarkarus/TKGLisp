#ifndef TKG_LIST_HPP
#define TKG_LIST_HPP

namespace tkg
{
    class Value;

    class List
    {
    private:
        Value *value_;
        Value *next_;

    public:
        List(Value value, Value next);
    
        Value get_value();

        Value get_next();
    };

    Value cons(Value left, Value right);

    Value car(Value value);

    Value cdr(Value value);

    bool isList(Value value);

    extern const Value NIL;
}

#endif // TKG_LIST_HPP
