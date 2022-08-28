#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "../Types/Component.hpp"
#include "../Types/Primitive.hpp"
#include "../Types/Element.hpp"
#include "../Handlers/PropHandlers.hpp"
/**
 * A class used to create Elements from Component vectors
 */
class ElementHandlers {
    public:
        static std::shared_ptr<DocumentTag> buildDocumentTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<Tag> buildTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<CloseTagElement> buildCloseTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);
        
        static std::shared_ptr<CommentTagElement> buildCommentTagElement(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);

        static std::shared_ptr<NestedString> buildNestedString(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index,  
            size_t &start);

        static void IgnoreWhiteSpace( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
        
        static void IncrementIndex( 
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
};