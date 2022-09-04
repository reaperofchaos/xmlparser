#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/CharType.h"

/**
 * A class used to create Elements from Component vectors
 */
class CharacterUtilities {
    public: 
        static void IgnoreWhiteSpace( 
            std::vector<std::shared_ptr<Character>> &characters,
            size_t &m_index);

        static void IncrementIndex( 
            std::vector<std::shared_ptr<Character>> &characters,
            size_t &m_index);
};