#ifndef TKG_VALUE_SPECIAL_FORM_HPP
#define TKG_VALUE_SPECIAL_FORM_HPP

#include "enum_utils.hpp"

namespace tkg
{
    enum class SpecialForm : detail::enum_fast_int
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

    constexpr std::string keyword_to_string(SpecialForm form)
    {
        return enum_to_lower_string(form);
    }

}

#endif // TKG_VALUE_SPECIAL_FORM_HPP
