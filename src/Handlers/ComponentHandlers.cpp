#include "ComponentHandlers.hpp"

std::shared_ptr<StringPrimitive> ComponentHandlers::buildStringPrimitive(
    std::shared_ptr<Component> &text, 
    size_t &m_index)
{
    m_index++;
    return std::make_shared<StringPrimitive>(std::dynamic_pointer_cast<StringType>(text));
}

//Creates a document tag element
std::shared_ptr<DocumentTag> ComponentHandlers::buildDocumentTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<DocumentTypeOpenTag> openTag = std::dynamic_pointer_cast<DocumentTypeOpenTag>(components[start]); 
    m_index++; 
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<Name> propName = std::dynamic_pointer_cast<Name>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<CloseTag> closeTag= std::dynamic_pointer_cast<CloseTag>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    return std::make_shared<DocumentTag>(openTag, tagName,  propName, closeTag);
}

std::shared_ptr<Tag> ComponentHandlers::buildTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<OpenTag> openTag = std::dynamic_pointer_cast<OpenTag>(components[start]); 
    m_index++;
    std::cout << components[m_index]->inspect() << "\n";
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::cout << components[m_index]->inspect() << "\n";

    if(components[m_index]->type() == ComponentType::CloseTag)
    {
        std::shared_ptr<CloseTag> closeTag = std::dynamic_pointer_cast<CloseTag>(components[m_index]); 
        m_index++;
        ComponentHandlers::IgnoreWhiteSpace(components, m_index);
        return std::make_shared<OpenTagElement>(openTag, tagName, closeTag);
    }

    if(components[m_index]->type() == ComponentType::ClosingCloseTag)
    {
        std::shared_ptr<ClosingCloseTag> closingCloseTag = std::dynamic_pointer_cast<ClosingCloseTag>(components[m_index]); 
        m_index++;
        ComponentHandlers::IgnoreWhiteSpace(components, m_index);
        return std::make_shared<SelfClosingTagElement>(openTag, tagName, closingCloseTag);
    }

    return {};
}

void ComponentHandlers::IgnoreWhiteSpace( 
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    while(components[m_index]->type() == ComponentType::WhiteSpaces)
    {
        m_index++;
    } 
}