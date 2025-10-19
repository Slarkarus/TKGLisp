#ifndef TKG_INTEGER_HPP
#define TKG_INTEGER_HPP

#include <iostream>
#include <vector>
#include <string>

namespace tkg
{
    class Integer
    {
    private:
        int64_t data_;

    public:
        Integer()
        {
            data_ = 0;
        }

        template <typename T>
            requires(std::is_integral_v<T> && !std::is_same_v<T, bool>)
        Integer(T value) : data_(static_cast<int64_t>(value))
        {
        }

        std::string get_as_string() const
        {
            return std::to_string(data_);
        }

        friend std::ostream &operator<<(std::ostream &output, const Integer &value)
        {
            return output << value.get_as_string();
        }
    };
}

#endif // TKG_INTEGER_HPP
