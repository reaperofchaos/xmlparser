#pragma once

#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Types/CharType.h"
#include "Types/Component.h"
#include "Tokenizer.h"
#include "Handlers/TokenHandlers.h"
#include "Utils/CharacterUtilities.h"
/**
 * @brief Class that takes tokens  and 
 * analyzes them further to create primitives
 * 
 */
class CharacterReader {
    private:
        std::vector<std::shared_ptr<Character>> m_tokens;
        std::vector<std::shared_ptr<Component>> m_components;
        size_t m_index = 0; // position in string

    public:
        CharacterReader(std::vector<std::shared_ptr<Character>> tokens){
            this->m_tokens = tokens; 
        }

        std::vector<std::shared_ptr<Character>> getTokens(){return m_tokens;}
        std::vector<std::shared_ptr<Component>> getComponents(){return m_components;}

        static void read_str(std::string input);
        std::shared_ptr<Component> next();
        void build_components();
        void displayCharacterTokens();
        void displayComponents();
};
