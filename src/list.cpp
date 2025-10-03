#include "list.hpp"
#include "value.hpp"

namespace tkg
{
    const Value NIL = List(None, None);

    List::List(Value value, Value next)
    {
        value_ = &value;
        next_ = &next;
    }

    Value List::get_value()
    {
        return *value_;
    }

    Value List::get_next()
    {
        return *next_;
    }

    Value cons(Value left, Value right)
    {
        return List(left, right);
    }

    Value car(Value value)
    {
        List list = value.get_as_raw<List>();
        return list.get_value();
    }

    Value cdr(Value value)
    {
        List list = value.get_as_raw<List>();
        return list.get_next();
    }

}