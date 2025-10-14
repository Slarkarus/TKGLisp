#include "parser.hpp"
#include "value.hpp"
#include <string>

namespace tkg
{
    Value Parser::parse()
    {
        current_state_ = ParserState::Processing;

        while (!is_end())
        {
            skip_empty();
            switch (input_[offset_])
            {
            case '"': {
                uint32_t begin = offset_;
                if(!skip_for_symbols<'"'>()){
                    return process_error<ParserError::MissingSecondDoubleQuote>();
                }

                if(begin + 2 == offset_){ // String is empty
                    append_value("");
                }
                else{ // String isn't empty
                    append_value(input_.substr(begin+1, offset_-2));
                }
                break;
            }
            case '(':
                
                break;
            case ')':
                if(values_.empty()){
                    return process_error<ParserError::MissingLeftBracket>();
                }
                break;
            case ';':
                if (!skip_for_symbols<';'>())
                {
                    return process_error<ParserError::MissingSecondSemilicon>();
                }
                break;
            default:
                return process_error<ParserError::UndefinedSymbol>();
            }
        }

        if(!values_.empty()){
            return process_error<ParserError::MissingRightBracket>();
        }
        current_state_ = ParserState::Done;
        return None;
    }



    inline void Parser::skip_empty()
    {
        do
        {
            offset_++;
        } while (!is_end() &&
                 (input_[offset_] == ' ' ||
                  input_[offset_] == '\n' ||
                  input_[offset_] == '\0'));
    }

    template <char... chars>
    inline bool Parser::skip_for_symbols()
    {
        do
        {
            offset_++;
        } while (!is_end() && !((input_[offset_] == chars) || ...));

        if (is_end())
        {
            return false;
        }
        offset_++;

        return true;
    }

    inline bool Parser::is_end()
    {
        return offset_ >= input_.size();
    }

    template<ParserError error>
    inline Value Parser::process_error(){
        current_state_ = ParserState::Error;
        current_error_ = error;
        return None;
    }

    void Parser::append_value(Value &&x){
        values_.top().push_back(x);
    }
}
// Вычисляется головной элемент списка, но не всегда это нужно

// Например if (вычисляет первый элемент, но если второй false, то его не вычисляем)