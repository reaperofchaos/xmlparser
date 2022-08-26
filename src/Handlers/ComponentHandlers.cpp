#include "ComponentHandlers.hpp"

std::shared_ptr<Primitive> ComponentHandlers::buildPrimitive(
    std::vector<std::shared_ptr<Component>> &components, 
    size_t &m_index)
{
    size_t start = m_index; 
    switch(components[start]->type()){
        case ComponentType::Name:
            return ComponentHandlers::buildBooleanPrimitive(components[start], m_index);
        case ComponentType::NumberType:
            return ComponentHandlers::buildNumberPrimitive(components, m_index);
        case ComponentType::StringType:
            return ComponentHandlers::buildStringPrimitive(components, m_index);
        default:
            m_index++;
            return NULL; 
    }
    return NULL; 
}

std::shared_ptr<BooleanPrimitive> ComponentHandlers::buildBooleanPrimitive(
    std::shared_ptr<Component> &text, 
    size_t &m_index)
{
    m_index++;
    return std::make_shared<BooleanPrimitive>(std::dynamic_pointer_cast<Name>(text));
}

std::shared_ptr<StringPrimitive> ComponentHandlers::buildStringPrimitive(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    std::vector<std::shared_ptr<Component>> characters;
    m_index++; 
    while((components[m_index]->type() == ComponentType::OpenTag ||
        components[m_index]->type() == ComponentType::ClosingOpenTag))
    {
        characters.push_back(components[m_index]);
        m_index++;
    }
    return std::make_shared<StringPrimitive>(characters);
}

std::shared_ptr<NumberPrimitive> ComponentHandlers::buildNumberPrimitive(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    m_index++;
    return std::make_shared<NumberPrimitive>(std::dynamic_pointer_cast<NumberType>(components[m_index-1]));
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

std::shared_ptr<ObjectPrimitive> ComponentHandlers::buildObject(
    std::vector<std::shared_ptr<Component>> &components,
    size_t &m_index)
{
    std::vector<std::shared_ptr<ObjectPair>> objectPairs; 
    while(components[m_index]->type() != ComponentType::CloseObject)
    {
        m_index++;
        ComponentHandlers::IgnoreWhiteSpace(components, m_index);

        //Function to build an object pair
        if(components[m_index]->type() == ComponentType::Name){
            std::shared_ptr<Name> key = std::dynamic_pointer_cast<Name>(components[m_index]); 
            m_index++;
            ComponentHandlers::IgnoreWhiteSpace(components, m_index);
            if(components[m_index]->type() == ComponentType::ColonComponent)
            {
                m_index++;
            }

            ComponentHandlers::IgnoreWhiteSpace(components, m_index);
            std::shared_ptr<Primitive> primitive = ComponentHandlers::buildPrimitive(components, m_index);
            ComponentHandlers::IgnoreWhiteSpace(components, m_index);
            if(components[m_index]->type() == ComponentType::CommaComponent)
            {
                m_index++;
                ComponentHandlers::IgnoreWhiteSpace(components, m_index);
            }

            objectPairs.push_back(std::make_shared<ObjectPair>(key, primitive));
        }
    }

    m_index++;
    return std::make_shared<ObjectPrimitive>(objectPairs);
}