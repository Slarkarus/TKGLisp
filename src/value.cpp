#include <iostream>
#include "value.hpp"
namespace tkg
{
    std::ostream &Value::print(std::ostream &output)
    {
        switch (type_)
        {
        case ValueType::INTEGER:
            output << std::get<Integer>(data_);
            break;
        case ValueType::STRING:
            output << "\"" << std::get<std::string>(data_) << "\"";
            break;
        case ValueType::BOOL:
            output << (std::get<bool>(data_) ? "true" : "false");
            break;
        case ValueType::LIST:
            output << "(" << "TODO: Realize List output" << ")";
            break;
        case ValueType::NONE:
            output << "None";
            break;
        default:
            break;
        }
        return output;
    }

    const Value None = nullptr;
}