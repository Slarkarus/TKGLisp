#include <iostream>
#include <cmath>

#include "value/value.hpp"
#include "config.hpp"
#include "magic_enum.hpp"

namespace tkg
{
    std::string Value::get_as_string()
    {
        switch (type_)
        {
        case ValueType::Integer:
            return std::get<Integer>(data_).get_as_string();
        case ValueType::Double:
            return std::to_string(std::get<double>(data_));
        case ValueType::String:
            return "\"" + std::get<std::string>(data_) + "\"";
        case ValueType::Bool:
            return (std::get<bool>(data_) ? "true" : "false");
        case ValueType::List:
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

            if (!is_nil(cur_value) && !cur_value.is_same_type(ValueType::None))
            {
                if (!first)
                    result += " ";
                result += cur_value.get_as_string();
            }

            return "(" + result + ")";
        }
        case ValueType::None:
            return "";
        case ValueType::Token:
            return std::get<Token>(data_).get_name();
        case ValueType::BinaryOperation:
            return keyword_to_string(std::get<BinaryOperation>(data_));
        case ValueType::BinaryPredicate:
            return keyword_to_string(std::get<BinaryPredicate>(data_));
        case ValueType::SpecialForm:
            return keyword_to_string(std::get<SpecialForm>(data_));
        }
    }

    std::string Value::get_as_debug_string()
    {
        switch (type_)
        {
        case ValueType::Integer:
        case ValueType::Double:
        case ValueType::String:
        case ValueType::Bool:
        case ValueType::Token:
        case ValueType::BinaryOperation:
        case ValueType::BinaryPredicate:
        case ValueType::SpecialForm:
            return static_cast<std::string>(magic_enum::enum_name(type_)) + ":" + get_as_string();
        case ValueType::List:
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
                std::string tmp = cur_list.get_value().get_as_debug_string();

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

            if (!is_nil(cur_value) && !cur_value.is_same_type(ValueType::None))
            {
                if (!first)
                    result += " ";
                result += cur_value.get_as_debug_string();
            }

            return "List:(" + result + ")";
        }
        case ValueType::None:
            return static_cast<std::string>(magic_enum::enum_name(type_));
        }
    }

    bool Value::is_same_type(ValueType type) const noexcept
    {
        return type_ == type;
    }

    bool Value::operator==(const Value &other) const
    {
        if (!is_same_type(other.type_))
        {
            return false;
        }

        switch (type_)
        {
        case ValueType::Double:
            return fabs(get_as_raw<double>() - other.get_as_raw<double>()) < DOUBLE_PRECISION;
        case ValueType::List:
            return car(*this) == car(other) && cdr(*this) == cdr(other);
        case ValueType::None:
            return true;
        case ValueType::Bool:
        case ValueType::Integer:
        case ValueType::String:
        case ValueType::Token:
        case ValueType::BinaryOperation:
        case ValueType::BinaryPredicate:
        case ValueType::SpecialForm:
            return data_ == other.data_;
        }

        return false;
    }

    bool is_nil(Value value)
    {
        if (!value.is_same_type(ValueType::List))
        {
            return false;
        }
        List list = value.get_as_raw<List>();

        return list.get_value().is_same_type(ValueType::None) &&
               list.get_next().is_same_type(ValueType::None);
    }

    const Value None = nullptr;
    const Value NIL = cons(None, None);
}