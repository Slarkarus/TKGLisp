#include <type_traits>
#include <string>
#include <variant>
#include "integer.hpp"
#include "list.hpp"

#ifndef TKG_VALUE_HPP
#define TKG_VALUE_HPP

namespace tkg
{
    struct List;

    enum ValueType
    {
        INTEGER,
        STRING,
        BOOL,
        LIST,
        NONE
    };

    // Тип к которому приводится тип, который передаётся в ValueTemplate
    template <typename T>
    using StoredType =
        std::conditional_t<std::is_convertible_v<std::decay_t<T>, Integer> && !std::is_same_v<std::decay_t<T>, bool>, Integer,
                           std::conditional_t<std::is_convertible_v<std::decay_t<T>, std::string>, std::string, std::decay_t<T>>>;

    // Типы, только для которых возможно создание ValueTemplate
    template <typename T>
    concept AllowedValueType =
        std::same_as<T, Integer> ||
        std::same_as<T, std::string> ||
        std::same_as<T, bool> ||
        std::same_as<T, List> ||
        std::same_as<T, std::nullptr_t>;

    class Value
    {
    private:
        ValueType type_;
        std::variant<std::monostate, Integer, std::string, bool, List> data_;

    public:
        Value() : type_(ValueType::NONE), data_(std::monostate{}) {}

        Value(std::nullptr_t) : type_(ValueType::NONE), data_(std::monostate{}) {}

        template <typename T>
            requires(!std::same_as<std::decay_t<T>, Value>)
        Value(T &&value_)
        {
            using Stored = StoredType<T>;

            static_assert(AllowedValueType<Stored>,
                          "Value type must be Integer or std::string or ConsList or bool or nullptr");

            if constexpr (std::same_as<Stored, Integer>)
            {
                type_ = ValueType::INTEGER;
                data_ = Integer(value_);
            }
            else if constexpr (std::same_as<Stored, std::string>)
            {
                type_ = ValueType::STRING;
                data_ = std::string(value_);
            }
            else if constexpr (std::same_as<Stored, bool>)
            {
                type_ = ValueType::BOOL;
                data_ = value_;
            }
            else if constexpr (std::same_as<Stored, List>)
            {
                type_ = ValueType::LIST;
                data_ = value_;
            }
            else if constexpr (std::same_as<Stored, std::nullptr_t>)
            {
                type_ = ValueType::NONE;
                data_ = std::monostate{};
            }
        }

        std::ostream &print(std::ostream &output);

        friend std::ostream &operator<<(std::ostream &output, Value &value) { return value.print(output); }
    };

#define None nullptr;
}

#endif // TKG_VALUE_HPP