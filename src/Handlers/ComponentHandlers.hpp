#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.hpp"
#include "../Types/Primitive.hpp"
#include "../Types/Element.hpp"

class ComponentHandlers {
    public:
        static std::shared_ptr<StringPrimitive> buildStringPrimitive(
            std::shared_ptr<Component> &text, 
            size_t &m_index);
        
        static std::shared_ptr<DocumentTag> buildDocumentTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<Tag> buildTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);

        static void IgnoreWhiteSpace( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
};