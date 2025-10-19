#include "trie.hpp"

namespace tkg
{
    void Trie::add_string(Value *value, const std::string &value_str)
    {
        TrieNode *current_node = root;
        for (auto c : value_str)
        {
            if (current_node->next_[c] == nullptr)
            {
                current_node->next_[c] = new TrieNode;
            }
            current_node = current_node->next_[c];
        }
        current_node->current_value = value;
    }

    Value Trie::get_value(const std::string &value_str)
    {
        TrieNode *current_node = root;

        for (auto c : value_str)
        {
            if (current_node->next_[c] == nullptr)
            {
                return None;
            }
            current_node = current_node->next_[c];
        }

        return current_node->current_value;
    }
}
