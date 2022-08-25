#include "ComponentHandlers.hpp"

std::shared_ptr<StringPrimitive> ComponentHandlers::buildPrimitve(
    std::shared_ptr<Component> &text, 
    size_t &m_index)
{
    switch(text->type()){
        case ComponentType::Name:
            return ComponentHandlers::buildBooleanPrimitive(text, m_index);
        case ComponentType::NumberType:
            return ComponentHandlers::buildNumberPrimitive(text, m_index);
        case ComponentType::StringType:
            return ComponentHandlers::buildStringPrimitive(text, m_index);
        default:
        m_index++; 
    }
}

std::shared_ptr<StringPrimitive> ComponentHandlers::buildBooleanPrimitive(
    std::shared_ptr<Component> &text, 
    size_t &m_index)
{
    m_index++;
    return std::make_shared<BooleanPrimitive>(std::dynamic_pointer_cast<Name>(text));
}

std::shared_ptr<StringPrimitive> ComponentHandlers::buildStringPrimitive(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,
    size_t &start)
{
    m_index++;
    std::vector<std::shared_ptr<Component> characters = []; 
    while(components[m_index]->type() == ComponentType::OpenTag ||
        components[m_index]->type() == ComponentType::ClosingOpenTag)
    {
        numbers.push_back(components[m_index]);
        m_index++;
    }
    return std::make_shared<StringPrimitive>(characters);
}

std::shared_ptr<NumberPrimitive> ComponentHandlers::buildNumberPrimitive(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,
    size_t &start)
{
    std::vector<std::shared_ptr<NumberType> numbers = []; 
    while(components[m_index]->type() == ComponentType::NumberType){
        numbers.push_back(std::dynamic_pointer_cast<NumberType>(components[m_index]));
        m_index++;
    }
    return std::make_shared<NumberPrimitive>(numbers);
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
    if(components[m_index]->type() == ComponentType::Name)
    {
        std::cout << components[m_index]->getValue() << " is a prop!" << "\n"; 
        m_index++;
        ComponentHandlers::IgnoreWhiteSpace(components, m_index);
        std::cout << components[m_index]->inspect() << "\n"; 

    }
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

std::shared_ptr<CloseTagElement> ComponentHandlers::buildCloseTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    // std::cout << components[start]->getValue() << "\n";
    std::shared_ptr<ClosingOpenTag> openClosingTag = std::dynamic_pointer_cast<ClosingOpenTag>(components[start]);
    
    std::cout << openClosingTag->inspect() << "\n";
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::cout << components[m_index]->inspect() << "\n";
    std::shared_ptr<Name> tagName = std::dynamic_pointer_cast<Name>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::cout << components[m_index]->inspect() << "\n";
    std::shared_ptr<CloseTag> closeTag = std::dynamic_pointer_cast<CloseTag>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::cout << components[m_index]->inspect() << "\n";
    return std::make_shared<CloseTagElement>(openClosingTag, tagName, closeTag);
}

std::shared_ptr<CommentTagElement> ComponentHandlers::buildCommentTagElement(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<CommentOpenTag> openTag = std::dynamic_pointer_cast<CommentOpenTag>(components[start]); 
    m_index++;
    std::cout << components[m_index]->inspect() << "\n";
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<StringType> comment = std::dynamic_pointer_cast<StringType>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    std::shared_ptr<CommentCloseTag> closeTag = std::dynamic_pointer_cast<CommentCloseTag>(components[m_index]);
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    return std::make_shared<CommentTagElement>(openTag, comment, closeTag);
}

std::shared_ptr<NestedString> ComponentHandlers::buildNestedString(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index,  
    size_t &start)
{
    std::shared_ptr<StringType> stringValue = std::dynamic_pointer_cast<StringType>(components[start]); 
    m_index++;
    ComponentHandlers::IgnoreWhiteSpace(components, m_index);
    return std::make_shared<NestedString>(stringValue);
}