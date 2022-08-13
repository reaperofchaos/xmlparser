#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Types/CharType.hpp"
#include "Types/Primitive.hpp"
#include "Tokenizer.hpp"
#include "TokenHandlers.hpp"
/**
 * @brief Class that takes tokens  and 
 * analyzes them further to create primitives
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
        std::vector<std::shared_ptr<Primitive>> getPrimitives(){return m_primitives;}

        static void read_str(std::string input);
        std::shared_ptr<Primitive> next();
        void build_primitives();

        void displayCharacterTokens();
        void displayPrimitives();
};
