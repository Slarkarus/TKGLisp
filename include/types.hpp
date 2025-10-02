#include "integer.hpp"

#ifndef TKG_TYPES_HPP
#define TKG_TYPES_HPP

namespace tkg
{

    class LispValue;

    class ConsList
    {
        LispValue *left;
        LispValue *right;
    };

    enum class LispValueType
    {
        integer,
        string,
        boolean,
        cons_list
    };

    union LispValueData
    {
        Integer *integer_data;
        std::string *string_data;
        bool bool_data;
        ConsList cons_list_data;
    };

    class LispValue
    {
    private:
        LispValueType type_;
        LispValueData data_;
    };
}

#endif // TKG_TYPES_HPP