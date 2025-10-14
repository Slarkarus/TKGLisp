#ifndef TKG_PARSER_HPP
#define TKG_PARSER_HPP

#include <string>
#include <stack>
#include <vector>
#include "value.hpp"

namespace tkg
{
    enum class ParserState : int_fast8_t
    {
        Empty,
        Processing,
        Error,
        Done
    };

    enum class ParserError : int_fast8_t
    {
        UndefinedBehaviour,
        MissingLeftBracket,
        MissingRightBracket,
        MissingSecondDoubleQuote,
        MissingSecondSemilicon,
        UndefinedSymbol
    };

    class Parser
    {
    private:
        uint32_t offset_;
        std::string &input_;
        ParserState current_state_;
        ParserError current_error_;
        std::stack <std::vector <Value>> values_;

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

    public:
        ParserState get_current_state()
        {
            return current_state_;
        }

        Parser(std::string &input) : input_(input), offset_(0) {}

        Value parse();
    };

}

#endif // TKG_PARSER_HPP
