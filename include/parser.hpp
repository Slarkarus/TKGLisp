#ifndef TKG_PARSER_HPP
#define TKG_PARSER_HPP

#include <string>
#include <stack>
#include <vector>

#include "string_utils.hpp"
#include "value.hpp"

namespace tkg
{
    enum class ParserState : uint_fast8_t
    {
        Empty,
        Processing,
        Error,
        Done
    };

    enum class ParserError : uint_fast8_t
    {
        MissingLeftBracket,
        MissingRightBracket,
        MissingSecondDoubleQuote,
        MissingSecondSemilicon,
        MissingGlobalLeftBracket
    };

    class Parser
    {
    private:
        StringOffset offset_;
        std::string &input_;
        ParserState current_state_;
        ParserError current_error_;
        std::stack<std::vector<Value>> values_;
        Value extracted_value_;

        void skip_empty();

        // Skip all symbols, after current symbol, while not found semilicon
        // Also skip founded symbol
        // Return false if don't found symbol
        template <char... chars>
        bool skip_for_symbols();

        bool is_end();

        template <ParserError error>
        Value process_error();

        void append_value(Value &&x);

        void extract_value_from_stack();

        Value parse_value_from_substring(StringOffset begin, StringOffset end);

    public:
        const StringOffset get_offset()
        {
            return offset_;
        }

        const std::string &get_input()
        {
            return input_;
        }

        ParserState get_current_state()
        {
            return current_state_;
        }

        ParserError get_current_error()
        {
            return current_error_;
        }

        Parser(std::string &input) : input_(input), offset_(0)
        {
            extracted_value_ = None;
        }

        Value parse();
    };

}

#endif // TKG_PARSER_HPP
