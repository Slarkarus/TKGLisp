#ifndef TKG_PARSER_HPP
#define TKG_PARSER_HPP

#include <string>
#include <stack>
#include <vector>

#include "string_utils.hpp"
#include "enum_utils.hpp"
#include "value/value.hpp"
#include "trie.hpp"

namespace tkg
{
    enum class ParserState : detail::enum_fast_int
    {
        Empty,
        Processing,
        Error,
        Done
    };

    enum class ParserError : detail::enum_fast_int
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
        std::string input_;
        ParserState current_state_;
        ParserError current_error_;
        std::stack<std::vector<Value>> values_;
        Value extracted_value_;
        Trie keyword_trie_;

        void skip_empty();

        // Skip all symbols, after current symbol, while not found semilicon
        // Also skip founded symbol
        // Return false if don't found symbol
        template <char... chars>
        bool skip_for_symbols();

        bool is_eof();

        template <ParserError error>
        Value process_error();

        void append_value(Value &&x);

        void extract_value_from_stack();

        Value parse_value_from_substring(StringOffset begin, StringOffset end);

        void fill_keyword_trie();

        void prepare_for_parsing(std::string &str);

    public:
        StringOffset get_offset()
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

        Parser() { fill_keyword_trie(); }

        Value parse(std::string &str);
    };

}

#endif // TKG_PARSER_HPP
