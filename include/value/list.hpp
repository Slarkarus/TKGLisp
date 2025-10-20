#ifndef TKG_VALUE_LIST_HPP
#define TKG_VALUE_LIST_HPP

#include <memory>

namespace tkg
{
    class Value;

    class List
    {
    private:
        std::shared_ptr<Value> value_;
        std::shared_ptr<Value> next_;

    public:
        List(std::shared_ptr<Value> value, std::shared_ptr<Value> next);

        Value get_value() const;

        Value get_next() const;

        bool operator==(const List &other) const;
    };

    Value car(Value value);

    Value cdr(Value value);

    bool is_list(Value value);
}

#endif // TKG_VALUE_LIST_HPP
