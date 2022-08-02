#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <optional>
#include <memory>
#include "Types/CharType.hpp"
#include "Tokenizer.hpp"
// #include "Node.hpp"

/**
 * @brief Class that takes tokens (string_view) and 
 * analyzes them further to assign a type
 * 
 */
class CharacterReader {
    private:
        std::vector<std::shared_ptr<Character>> m_tokens;

    public:
        CharacterReader(std::vector<std::shared_ptr<Character>> tokens){
            this->m_tokens = tokens; 
        }

        std::vector<std::shared_ptr<Character>> getTokens(){return m_tokens;}
        static void read_str(std::string input);
        void displayCharacterTokens();
};
