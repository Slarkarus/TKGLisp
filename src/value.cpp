#include <iostream>
#include "value.hpp"
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
            return  "(TODO: Realize List output)";
        case ValueType::NONE:
            return "None";
        default:
            break;
        }
        return "";
    }

    const Value None = nullptr;
}