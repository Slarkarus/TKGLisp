#ifndef TKG_PARSER_HPP
#define TKG_PARSER_HPP

#include <string>
#include <stack>
#include <vector>

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
        uint32_t offset_;
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

        Value parse_value_from_substring(uint32_t begin, uint32_t end);

    public:
        ParserState get_current_state()
        {
            return current_state_;
        }

        ParserError get_current_error()
        {
            return current_error_;
        }

        // Return current line number and column number (by offset)
        std::pair<uint32_t, uint32_t> get_current_position();

        // Return current line (by offset)
        std::string get_current_line();

        Parser(std::string &input) : input_(input), offset_(0)
        {
            extracted_value_ = None;
        }

        Value parse();
    };

}

#endif // TKG_PARSER_HPP
