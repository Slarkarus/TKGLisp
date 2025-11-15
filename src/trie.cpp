#include "trie.hpp"

namespace tkg
{
    void Trie::add_string(Value &&value, const std::string &value_str)
    {
        TrieNode *current_node = root_.get();
        for (auto c : value_str)
        {
            if (current_node->next[c] == nullptr)
            {
                current_node->next[c] = std::make_unique<TrieNode>();
            }
            current_node = current_node->next[c].get();
        }
        current_node->current_value = std::move(value);
        current_node->has_value = true;
    }

    void Trie::add_string(const Value &value, const std::string &value_str)
    {
        TrieNode *current_node = root_.get();
        for (auto c : value_str)
        {
            if (current_node->next[c] == nullptr)
            {
                current_node->next[c] = std::make_unique<TrieNode>();
            }
            current_node = current_node->next[c].get();
        }
        current_node->current_value = value;
        current_node->has_value = true;
    }

    Value Trie::get_value(const std::string &value_str) const
    {
        TrieNode *current_node = root_.get();

        for (auto c : value_str)
        {
            if (current_node->next[c] == nullptr)
            {
                return None;
            }
            current_node = current_node->next[c].get();
        }

        if (current_node->has_value)
        {
            return current_node->current_value;
        }

        return None;
    }
}
