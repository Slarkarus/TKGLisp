#include <vector>

#ifndef TKG_INTEGER_HPP
#define TKG_INTEGER_HPP

namespace tkg
{
    class Integer
    {
    private:
        int64_t data_;

    public:
        
        Integer(){
            data_ = 0;
        }

        template <typename T>
            requires (std::is_integral_v<T> && !std::is_same_v<T, bool>)
        Integer(T value) : data_(static_cast<int64_t>(value)) {}

        std::ostream& print(std::ostream &output) const {
            output << data_;
            return output;
        }

        friend std::ostream &operator<<(std::ostream &output, const Integer& value)
        {
            return value.print(output);
        }
    };
}

#endif // TKG_INTEGER_HPP