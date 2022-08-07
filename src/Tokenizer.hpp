#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <memory>
#include "Types/CharType.hpp"
#include "Types/Symbol.hpp"
/**
 * @brief Class to break down string into smaller chunks
 * which are either tags, strings or untracked 
 * new line or return characters
 * 
 */
class Tokenizer{
    private:
        std::string m_input; // string input
        size_t m_index = 0; // position in string
        std::vector<std::shared_ptr<Character>> tokens;

    public: 
        Tokenizer(std::string input)
        {
            this->m_input = input; 
        }

        std::vector<std::shared_ptr<Character>>getTokens(){return this->tokens;}
        std::shared_ptr<Character> next();
        void tokenize();
};