#include <memory>

#include "list.hpp"
#include "value.hpp"

namespace tkg
{
    List::List(std::shared_ptr<Value> value, std::shared_ptr<Value> next)
        : value_(value), next_(next) {}

    Value List::get_value()
    {
        return *value_;
    }

    Value List::get_next()
    {
        return *next_;
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

    bool is_list(Value value)
    {
        return value.is_same_type(ValueType::List);
    }
}
