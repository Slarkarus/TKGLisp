#ifndef TKG_STRING_UTILS_HPP
#define TKG_STRING_UTILS_HPP

#include <iostream>
#include <cstdint>
#include <string>
#include <type_traits>
#include <algorithm>

#include "magic_enum.hpp"

namespace tkg
{
    namespace detail
    {
        template <typename T>
        concept EnumType = std::is_enum_v<T>;
    }

    using StringOffset = uint32_t;
    using StringPosition = std::pair<StringOffset, StringOffset>;

    // Return current line number and column number (by offset)
    inline StringPosition get_current_position(const std::string &input, const StringOffset offset)
    {
        StringOffset column = 1;
        StringOffset line = 1;
        StringOffset temporary_offset = 0;

        while (temporary_offset < offset)
        {
            if (input[temporary_offset] == '\n')
            {
                column = 0;
                line++;
            }
            temporary_offset++;
            column++;
        }

        return StringPosition(line, column);
    }

    // Return current line (by offset)
    inline std::string get_current_line(const std::string &input, const StringOffset offset)
    {
        StringOffset left = offset;
        StringOffset right = offset;

        while (left > 0 && input[left] != '\n')
            left--;

        if (input[left] == '\n')
            left++;

        StringOffset size = input.size();

        while (right < size && input[right] != '\n')
            right++;

        right--;

        return input.substr(left, right - left + 1);
    }

    template <detail::EnumType T>
    void print_error(T error, std::string line, StringPosition pos)
    {
        std::cout << "Error on line: " << pos.first << ", column: " << pos.second << '\n';
        std::cout << "Line: " << line << '\n';
        std::cout << "      ";

        for (tkg::StringOffset i = 1; i < pos.second; ++i)
            std::cout << '^';

        std::cout << '#';

        for (tkg::StringOffset i = pos.second + 1; i <= line.size(); ++i)
            std::cout << "^";

        std::cout << '\n';
        std::cout << magic_enum::enum_type_name<T>() << ": " << magic_enum::enum_name(error) << '\n';
    }

    template <detail::EnumType T>
    consteval std::string enum_to_lower_string(T enum_element)
    {
        std::string result = static_cast<std::string>(magic_enum::enum_name(enum_element));

        std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                       { return std::tolower(c); });
        return result;
    }
}

#endif // TKG_STRING_UTILS_HPP
