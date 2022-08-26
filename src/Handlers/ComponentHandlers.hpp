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
        static std::shared_ptr<Primitive> buildPrimitive(
            std::vector<std::shared_ptr<Component>> &components, 
            size_t &m_index);

        static std::shared_ptr<StringPrimitive> buildStringPrimitive(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);
        
        static std::shared_ptr<BooleanPrimitive> buildBooleanPrimitive(
            std::shared_ptr<Component> &text, 
            size_t &m_index);
        
        static std::shared_ptr<NumberPrimitive> buildNumberPrimitive(
            std::vector<std::shared_ptr<Component>> &components,
            size_t &m_index);

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
};