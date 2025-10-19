#ifndef TKG_ENUM_UTILS_HPP
#define TKG_ENUM_UTILS_HPP

#include <type_traits>
#include <cstdint>
#include <algorithm>

#include "magic_enum.hpp"

namespace tkg
{
    namespace detail
    {
        template <typename T>
        concept EnumType = std::is_enum_v<T>;

        using enum_fast_int = uint_fast8_t;
    }

    template <detail::EnumType T>
    constexpr std::string enum_to_lower_string(T enum_element)
    {
        std::string result = static_cast<std::string>(magic_enum::enum_name(enum_element));

        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                       { return std::tolower(c); });
        return result;
    }
}

#endif // TKG_ENUM_UTILS_HPP
