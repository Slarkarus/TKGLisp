#ifndef TKG_VALUE_VALUE_HPP
#define TKG_VALUE_VALUE_HPP

#include <type_traits>
#include <string>
#include <variant>

#include "binary_operation.hpp"
#include "binary_predicate.hpp"
#include "special_form.hpp"
#include "integer.hpp"
#include "list.hpp"

namespace tkg
{

    class Token
    {
    private:
        std::string name_;

    public:
        Token(const std::string &name) : name_(name) {}

        Token(std::string &&name) : name_(std::move(name)) {}

        const std::string &get_name()
        {
            return name_;
        }
    };

    namespace detail
    {
        // Тип к которому приводится тип, который передаётся в Value
        template <typename T>
        using StoredType =
            std::conditional_t<std::is_convertible_v<std::decay_t<T>, Integer> && !std::is_same_v<std::decay_t<T>, bool>, Integer,
                               std::conditional_t<std::is_convertible_v<std::decay_t<T>, std::string>, std::string,
                                                  std::conditional_t<std::is_floating_point_v<std::decay_t<T>>, double, std::decay_t<T>>>>;

        // Типы, только для которых возможно создание Value
        template <typename T>
        concept AllowedValueType =
            std::same_as<T, Integer> ||
            std::same_as<T, double> ||
            std::same_as<T, std::string> ||
            std::same_as<T, bool> ||
            std::same_as<T, List> ||
            std::same_as<T, std::nullptr_t> ||
            std::same_as<T, Token>;
    }

    enum class ValueType : uint_fast8_t
    {
        Integer,
        Double,
        String,
        Bool,
        List,
        None,
        Token
    };

    class Value
    {
    private:
        ValueType type_;
        std::variant<std::monostate, Integer, double, std::string, bool, List, Token> data_;

    public:
        Value() : type_(ValueType::None), data_(std::monostate{}) {}

        Value(std::nullptr_t) : type_(ValueType::None), data_(std::monostate{}) {}

        template <typename T>
            requires(!std::same_as<std::decay_t<T>, Value>)
        Value(T &&value_)
        {
            using Stored = detail::StoredType<T>;

            static_assert(detail::AllowedValueType<Stored>,
                          "Value type must be Integer or double or std::string or ConsList or bool or nullptr or Token");

            if constexpr (std::same_as<Stored, Integer>)
            {
                type_ = ValueType::Integer;
                data_ = Integer(value_);
            }
            else if constexpr (std::same_as<Stored, double>)
            {
                type_ = ValueType::Double;
                data_ = value_;
            }
            else if constexpr (std::same_as<Stored, std::string>)
            {
                type_ = ValueType::String;
                data_ = std::string(value_);
            }
            else if constexpr (std::same_as<Stored, bool>)
            {
                type_ = ValueType::Bool;
                data_ = value_;
            }
            else if constexpr (std::same_as<Stored, List>)
            {
                type_ = ValueType::List;
                data_ = value_;
            }
            else if constexpr (std::same_as<Stored, std::nullptr_t>)
            {
                type_ = ValueType::None;
                data_ = std::monostate{};
            }
            else if constexpr (std::same_as<Stored, Token>)
            {
                type_ = ValueType::Token;
                data_ = value_;
            }
        }

        template <typename T>
        const detail::StoredType<T> &get_as_raw() const
        {
            using Stored = detail::StoredType<T>;
            static_assert(detail::AllowedValueType<Stored>,
                          "Value type must be Integer or double or std::string or ConsList or bool or nullptr or Token");
            if (auto ptr = std::get_if<Stored>(&data_))
            {
                return *ptr;
            }
            throw std::bad_variant_access();
        }

        std::string get_as_string();

        friend std::ostream &operator<<(std::ostream &output, Value &value)
        {
            return output << value.get_as_string();
        }

        bool is_same_type(ValueType type);
    };

    template <typename T1, typename T2>
    Value cons(T1 &&left, T2 &&right)
    {
        return List(std::make_shared<Value>(std::forward<T1>(left)),
                    std::make_shared<Value>(std::forward<T2>(right)));
    }

    bool is_nil(Value value);

    extern const Value None;
    extern const Value NIL;
}

#endif // TKG_VALUE_VALUE_HPP
