#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Types/CharType.hpp"
#include "Types/Primitive.hpp"
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
        std::vector<std::shared_ptr<Primitive>> m_primitives;
        size_t m_index = 0; // position in string

    public:
        CharacterReader(std::vector<std::shared_ptr<Character>> tokens){
            this->m_tokens = tokens; 
        }

        std::vector<std::shared_ptr<Character>> getTokens(){return m_tokens;}
        static void read_str(std::string input);
        std::shared_ptr<Primitive> next();
        void build_primitives();

        void displayCharacterTokens();
};
