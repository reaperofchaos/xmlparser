#include "ElementBuilder.hpp"

std::shared_ptr<Element>ElementBuilder::next(){
    size_t start = this->m_index;

    while (this->m_index < this->m_components.size())
    {
        std::cout << m_components[m_index]->inspect() << "\n"; 
        switch(m_components[m_index]->type())
        {
            case ComponentType::DocumentTypeOpenTag:
                return ComponentHandlers::buildDocumentTagElement(m_components, m_index, start);
            case ComponentType::OpenTag:
                return ComponentHandlers::buildTagElement(m_components, m_index, start);
            case ComponentType::ClosingOpenTag:
                return ComponentHandlers::buildCloseTagElement(m_components, m_index, start);
            case ComponentType::CommentOpenTag:
                return ComponentHandlers::buildCommentTagElement(m_components, m_index, start); 
            case ComponentType::StringType:
                return ComponentHandlers::buildNestedString(m_components, m_index, start);    
            default:
                    m_index++;
                    return {};
        }
        return {};

    } 
    return {};

}

/**
 * @brief Builds primitives from components
 * 
 */
void ElementBuilder::buildElements() 
{
    std::cout << "building elements \n"; 
    while (auto element = this->next()) 
    {
        this->m_elements.push_back(element);
    }
}

/** 
 * function to read a string, 
 * tokenizes and analyzes the tokens 
 * and returns an Abstract Syntax Tree
 **/
void ElementBuilder::read_str(std::string input) 
{
    Tokenizer tokenizer = Tokenizer(input);
    tokenizer.tokenize();
    std::vector<std::shared_ptr<Character>>tokens = tokenizer.getTokens(); 
    std::cout << "Total tokens " << tokens.size() << "\n"; 
    CharacterReader reader = CharacterReader(tokens);  
    reader.build_components();
    std::vector<std::shared_ptr<Component>>components = reader.getComponents(); 
    std::cout << "Total components " << components.size() << "\n"; 
    //reader.displayComponents();
    ElementBuilder elementBuilder(components);
    elementBuilder.buildElements();
    std::vector<std::shared_ptr<Element>>elements = elementBuilder.getElements(); 
    std::cout << "Total elements " << elements.size() << "\n"; 
    elementBuilder.displayElements();
}

void ElementBuilder::displayElements(){
    for(auto element : this->m_elements)
    {
        std::cout << element->inspect();
    }
}