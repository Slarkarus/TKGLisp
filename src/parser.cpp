#include <string>

#include "parser.hpp"
#include "value/value.hpp"

namespace tkg
{
    Value Parser::parse()
    {
        current_state_ = ParserState::Processing;

        skip_empty();
        while (!is_eof())
        {
            skip_empty();

            if (is_eof())
            {
                break;
            }

            switch (input_[offset_])
            {
            case '"':
            {
                StringOffset begin = offset_;
                if (!skip_for_symbols<'"'>())
                {
                    return process_error<ParserError::MissingSecondDoubleQuote>();
                }

                if (begin + 2 == offset_) // String is empty
                {
                    append_value("");
                }
                else // String isn't empty
                {
                    append_value(input_.substr(begin + 1, offset_ - begin - 2));
                }
                break;
            }
            case '(':
                values_.push(std::vector<Value>());
                offset_++;
                break;
            case ')':
                if (values_.empty())
                {
                    return process_error<ParserError::MissingLeftBracket>();
                }

                extract_value_from_stack();

                if (values_.size() > 0)
                {
                    values_.top().push_back(extracted_value_);
                }
                offset_++;
                break;
            case ';':
                if (!skip_for_symbols<';'>())
                {
                    return process_error<ParserError::MissingSecondSemilicon>();
                }
                break;
            default:
            {
                if (values_.empty())
                {
                    return process_error<ParserError::MissingGlobalLeftBracket>();
                }
                StringOffset begin = offset_;
                // This line is reachable only after skip_empty
                // And if input_[offset_] symbol isn't space, bracket, or semilicon
                skip_for_symbols<' ', ')', '(', '\n', '\0', ';'>();
                offset_--; // We moved at least 2 character right in line before
                if (offset_ < begin + 1)
                {
                    return process_error<ParserError::MissingRightBracket>();
                }
                values_.top().push_back(parse_value_from_substring(begin, offset_ - 1));
                break;
            }
            }
        }

        if (!values_.empty())
        {
            return process_error<ParserError::MissingRightBracket>();
        }
        current_state_ = ParserState::Done;
        return extracted_value_;
    }

    inline void Parser::skip_empty()
    {
        while (!is_eof() &&
               (input_[offset_] == ' ' ||
                input_[offset_] == '\n' ||
                input_[offset_] == '\0'))
        {
            offset_++;
        }
    }

    template <char... chars>
    inline bool Parser::skip_for_symbols()
    {
        do
        {
            offset_++;
        } while (!is_eof() && !((input_[offset_] == chars) || ...));

        if (is_eof())
        {
            return false;
        }
        offset_++;

        return true;
    }

    inline bool Parser::is_eof()
    {
        return offset_ >= input_.size();
    }

    template <ParserError error>
    inline Value Parser::process_error()
    {
        current_state_ = ParserState::Error;
        current_error_ = error;
        return None;
    }

    void Parser::append_value(Value &&x)
    {
        values_.top().push_back(x);
    }

    Value Parser::parse_value_from_substring(StringOffset begin, StringOffset end)
    {
        bool integer_or_double = true;
        bool has_dot = false;

        for (StringOffset i = begin; i <= end; ++i)
        {
            if (input_[i] == '.')
            {
                has_dot = !has_dot;
                if (!has_dot)
                {
                    integer_or_double = false;
                    break;
                }
            }
            else if (!('0' <= input_[i] && input_[i] <= '9'))
            {
                integer_or_double = false;
                break;
            }
        }

        std::string substr = input_.substr(begin, end - begin + 1);

        if (integer_or_double)
        {
            if (has_dot)
            {
                return Value(std::stod(substr));
            }
            return Value(std::stoll(substr));
        }

        if (substr == "true")
        {
            return Value(true);
        }
        else if (substr == "false")
        {
            return Value(false);
        }

        return Value(Token(substr));
    }

    void Parser::extract_value_from_stack()
    {
        extracted_value_ = NIL;
        std::vector<Value> &vec = values_.top();

        for (auto it = vec.rbegin(); it != vec.rend(); ++it)
        {
            extracted_value_ = cons(std::move(*it), extracted_value_);
        }

        values_.pop();
    }
}