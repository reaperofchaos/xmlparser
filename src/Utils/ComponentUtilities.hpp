#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.hpp"

/**
 * A class used to create Elements from Component vectors
 */
class ComponentUtilities {
    public:
        static void IgnoreWhiteSpace( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
        
        static void IncrementIndex( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
};