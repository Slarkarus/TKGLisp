#ifndef TKG_VALUE_SPECIAL_FORM_HPP
#define TKG_VALUE_SPECIAL_FORM_HPP

#include "string_utils.hpp"

namespace tkg
{
    enum class SpecialForm
    {
        Quote,
        Eval,
        TypeOf,
        Cons,
        Car,
        Cdr,
        If,
        Do,
        Print,
        Read,
        Def,
        Set
    };

    consteval std::string keyword_to_string(SpecialForm form)
    {
        return enum_to_lower_string(form);
    }

}

#endif // TKG_VALUE_SPECIAL_FORM_HPP
