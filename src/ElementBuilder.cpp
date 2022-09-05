#include "ElementBuilder.h"

std::shared_ptr<Element>ElementBuilder::next(){
    size_t start = this->m_index;

    while (this->m_index < this->m_components.size()-1)
    {
        switch(m_components[m_index]->type())
        {
            case ComponentType::DocumentTypeOpenTag:
                return ElementHandlers::buildDocumentTagElement(m_components, m_index, start);
            case ComponentType::OpenTag:
                return ElementHandlers::buildTagElement(m_components, m_index, start);
            case ComponentType::ClosingOpenTag:
                return ElementHandlers::buildCloseTagElement(m_components, m_index, start);
            case ComponentType::CommentOpenTag:
                std::cout << "Found a comment open tag \n"; 
                return ElementHandlers::buildCommentTagElement(m_components, m_index, start); 
            case ComponentType::StringType:
                return ElementHandlers::buildNestedString(m_components, m_index, start);    
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
std::shared_ptr<Node> ElementBuilder::read_str(std::string input) 
{
    Tokenizer tokenizer = Tokenizer(input);
    tokenizer.tokenize();
    std::vector<std::shared_ptr<Character>>tokens = tokenizer.getTokens(); 
    std::cout << "Total tokens " << tokens.size() << "\n"; 
    ComponentBuilder componentBuilder = ComponentBuilder(tokens);  
    componentBuilder.build_components();
    std::vector<std::shared_ptr<Component>>components = componentBuilder.getComponents(); 
    std::cout << "Total components " << components.size() << "\n"; 
    ElementBuilder elementBuilder(components);
    elementBuilder.buildElements();
    std::vector<std::shared_ptr<Element>>elements = elementBuilder.getElements(); 
    std::cout << "Total elements " << elements.size() << "\n"; 
    std::shared_ptr<Node> targetNode;
    std::shared_ptr<Node> tree = targetNode->createTree(elements);
    return tree; 
}

void ElementBuilder::displayElements(){
    for(auto element : this->m_elements)
    {
        std::cout << element->inspect();
    }
}