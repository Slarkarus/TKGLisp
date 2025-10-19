#ifndef TKG_VALUE_BINARY_OPERATION_HPP
#define TKG_VALUE_BINARY_OPERATION_HPP

#include "enum_utils.hpp"

namespace tkg
{
    enum class BinaryOperation : detail::enum_fast_int
    {
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        StrConcat
    };

    consteval std::string keyword_to_string(BinaryOperation operation)
    {
        switch (operation)
        {
        case BinaryOperation::Add:
            return "_+_";
        case BinaryOperation::Sub:
            return "_-_";
        case BinaryOperation::Mul:
            return "_*_";
        case BinaryOperation::Div:
            return "_/_";
        case BinaryOperation::Mod:
            return "_%_";
        case BinaryOperation::StrConcat:
            return "_++_";
        }
    }
}

#endif // TKG_VALUE_BINARY_OPERATION_HPP
