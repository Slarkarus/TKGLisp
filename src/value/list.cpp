#include <memory>

#include "value/value.hpp"

namespace tkg
{
    List::List(std::shared_ptr<Value> value, std::shared_ptr<Value> next)
        : value_(value), next_(next) {}

    Value List::get_value() const
    {
        return *value_;
    }

    Value List::get_next() const
    {
        return *next_;
    }

    bool List::operator==(const List &other) const
    {
        return get_value() == other.get_value() &&
               get_next() == other.get_next();
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
