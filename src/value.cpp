#include <iostream>
#include "value.hpp"
#include "list.hpp"

namespace tkg
{
    std::string Value::get_as_string()
    {
        switch (type_)
        {
        case ValueType::INTEGER:
            return std::get<Integer>(data_).get_as_string();
        case ValueType::STRING:
            return "\"" + std::get<std::string>(data_) + "\"";
        case ValueType::BOOL:
            return (std::get<bool>(data_) ? "true" : "false");
        case ValueType::LIST:
        {
            std::string result = "";
            Value cur_value = *this;
            bool first = true;

            while (is_list(cur_value))
            {
                if (is_nil(cur_value))
                {
                    break;
                }

                List cur_list = cur_value.get_as_raw<List>();
                std::string tmp = cur_list.get_value().get_as_string();

                if (!tmp.empty())
                {
                    if (first)
                        first = false;
                    else
                        result += " ";
                }

                result += tmp;
                cur_value = cur_list.get_next();
            }

            if (!is_nil(cur_value) && !cur_value.is_same_type(ValueType::NONE))
            {
                if (!first)
                    result += " ";
                result += cur_value.get_as_string();
            }

            return "(" + result + ")";
        }
        case ValueType::NONE:
            return "";
        default:
            break;
        }
        return "";
    }

    bool Value::is_same_type(ValueType type)
    {
        return type_ == type;
    }

    bool is_nil(Value value)
    {
        if (!value.is_same_type(ValueType::LIST))
        {
            return false;
        }
        List list = value.get_as_raw<List>();

        return list.get_value().is_same_type(ValueType::NONE) && list.get_next().is_same_type(ValueType::NONE);
    }

    const Value None = nullptr;
    const Value NIL = cons(None, None);
}