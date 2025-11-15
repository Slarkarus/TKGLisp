#ifndef TKG_VALUE_BINARY_PREDICATE_HPP
#define TKG_VALUE_BINARY_PREDICATE_HPP

#include "enum_utils.hpp"

namespace tkg
{
    enum class BinaryPredicate : detail::enum_fast_int
    {
        Less,
        Great,
        Equal,
        LessEqual,
        GreatEqual
    };

    constexpr std::string keyword_to_string(BinaryPredicate predicate)
    {
        switch (predicate)
        {
        case BinaryPredicate::Less:
            return "<";
        case BinaryPredicate::Great:
            return ">";
        case BinaryPredicate::Equal:
            return "==";
        case BinaryPredicate::LessEqual:
            return "<=";
        case BinaryPredicate::GreatEqual:
            return ">=";
        }
    }
}
#endif // TKG_VALUE_BINARY_PREDICATE_HPP
