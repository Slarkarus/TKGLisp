#ifndef TKG_LIST_HPP
#define TKG_LIST_HPP

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

        Value get_value();

        Value get_next();
    };

    Value cons(Value left, Value right);

    Value car(Value value);

    Value cdr(Value value);

    bool is_list(Value value);
}

#endif // TKG_LIST_HPP
