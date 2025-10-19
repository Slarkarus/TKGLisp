#ifndef TKG_PARSER_TRIE_HPP
#define TKG_PARSER_TRIE_HPP

#include <climits>
#include <memory>

#include "value/value.hpp"
#include "string_utils.hpp"

namespace tkg
{
    class Trie
    {
    private:
        struct TrieNode
        {
            std::array<std::unique_ptr<TrieNode>, UCHAR_MAX> next;
            Value current_value;
            bool has_value = false;
        };

        std::unique_ptr<TrieNode> root_;

    public:
        void add_string(const Value &value, const std::string &value_str);

        void add_string(Value &&value, const std::string &value_str);

        Value get_value(const std::string &value_str) const;

        Trie() : root_(std::make_unique<TrieNode>()) {}
    };
}

#endif // TKG_PARSER_TRIE_HPP
