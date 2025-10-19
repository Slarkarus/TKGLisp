#ifndef TKG_PARSER_TRIE_HPP
#define TKG_PARSER_TRIE_HPP

#include <climits>

#include "value/value.hpp"
#include "string_utils.hpp"

namespace tkg
{
    class Trie
    {
    private:
        struct TrieNode
        {
            TrieNode *next_[UCHAR_MAX];
            Value *current_value;
        };

        TrieNode *root;

    public:
        void add_string(Value *value, const std::string &value_str);

        Value get_value(const std::string &value_str);

        Trie()
        {
            root = new TrieNode;
        }
    };
}

#endif // TKG_PARSER_TRIE_HPP
