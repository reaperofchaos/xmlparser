#include "TokenHandlers.hpp"

std::shared_ptr<NumberType> TokenHandlers::buildNumberPrimitive(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<Number>> &numbers)
{
    std::cout << "Building a number primitive \n";
    
    while(m_tokens[m_index]->type() == CharacterType::Number)
    {
        numbers.push_back(std::make_shared<Number>(m_tokens[m_index]->getValue()));
        m_index++; 
    }
    return std::make_shared<NumberType>(numbers);
}

std::shared_ptr<CloseTag> TokenHandlers::buildCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    m_index++;
    std::cout << "Building a close bracket primitive \n";
    if(whiteSpaces.size() > 0){
        return std::make_shared<CloseTag>(whiteSpaces, 
            std::dynamic_pointer_cast<CloseBracket>(m_tokens[m_index-1]));
    }

    return std::make_shared<CloseTag>(
        std::dynamic_pointer_cast<CloseBracket>(m_tokens[m_index-1])); 
}

std::shared_ptr<CloseArray> TokenHandlers::buildCloseArray(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    std::cout << "Building an array close bracket primitive \n";
    if(whiteSpaces.size() > 0){
        return std::make_shared<CloseArray>(whiteSpaces,
            std::dynamic_pointer_cast<ArrayCloseBracket>(m_tokens[m_index]));
    }

    return std::make_shared<CloseArray>(std::dynamic_pointer_cast<ArrayCloseBracket>(m_tokens[m_index]));
    
}

std::shared_ptr<CloseObject> TokenHandlers::buildCloseObject(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    std::cout << "Building an object close bracket primitive \n";
    if(whiteSpaces.size() > 0){
        return std::make_shared<CloseObject>(whiteSpaces,
            std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[m_index]));
    }

    return std::make_shared<CloseObject>(std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[m_index]));
    
}

std::shared_ptr<WhiteSpaces> TokenHandlers::buildWhiteSpaces(
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    return std::make_shared<WhiteSpaces>(whiteSpaces);
}

std::shared_ptr<Name> TokenHandlers::buildName(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<Character>> &characters

)
{
    std::cout << "Building a name" << "\n";
    m_index++;
    while(m_tokens[m_index]->type() != CharacterType::WhiteSpace &&
    (m_tokens[m_index]->type() != CharacterType::Symbol && m_tokens[m_index]->symbolType() != SymbolType::CloseBracket) &&
    (m_tokens[m_index]->type() != CharacterType::Symbol && m_tokens[m_index]->symbolType() != SymbolType::EqualSymbol)
    )
    {
        characters.push_back(std::dynamic_pointer_cast<Character>(m_tokens[m_index]));
        m_index++;
    }
    return std::make_shared<Name>(
        std::dynamic_pointer_cast<Letter>(m_tokens[start]),
        characters);
}

std::shared_ptr<ClosingCloseTag> TokenHandlers::buildClosingCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start)
{
    std::cout << "Building a closing close tag primitive \n";
    if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace )
    {
        m_index++;
        while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
        {
            m_index++;
        }
    }else{
        m_index++;
    }
    m_index++; 
    std::cout << "value " << m_tokens[m_index-1]->getValue() << "\n";
    return std::make_shared<ClosingCloseTag>
        (
            std::dynamic_pointer_cast<ForwardSlash>(m_tokens[start]),
            std::dynamic_pointer_cast<CloseBracket>(m_tokens[m_index-1])
        );
}

std::shared_ptr<StringType> TokenHandlers::buildString(
        std::vector<std::shared_ptr<Character>> &m_tokens, 
        size_t &m_index,
        size_t &start,
        std::vector<std::shared_ptr<Character>> &characters, 
        SymbolType symbolType)
{
    std::cout << "Building a string \n";
    m_index++; 
    if(symbolType == SymbolType::SingleQuote)
    {
        while( m_tokens[m_index]->symbolType() != SymbolType::SingleQuote)
            {
                characters.push_back(m_tokens[m_index]);
                m_index++;
            }
        return std::make_shared<StringType>( 
            std::dynamic_pointer_cast<SingleQuote>(m_tokens[start]),
            characters,
            std::dynamic_pointer_cast<SingleQuote>(m_tokens[m_index])
        );
    }else{
        while( m_tokens[m_index]->symbolType() != SymbolType::Quote)
        {
            characters.push_back(m_tokens[m_index]);
            m_index++;
        }
        return std::make_shared<StringType>( 
            std::dynamic_pointer_cast<Quote>(m_tokens[start]),
            characters,
            std::dynamic_pointer_cast<Quote>(m_tokens[m_index])
        );
    }
}

std::shared_ptr<OpenArray> TokenHandlers::buildOpenArray(
        std::vector<std::shared_ptr<Character>> &m_tokens, 
        size_t &m_index,
        size_t &start,
        std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    std::cout << "Building an open array primitive \n";
    if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace){
        m_index++;
        while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
        {
            whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
            m_index++;
        }
        return std::make_shared<OpenArray>
        (
            std::dynamic_pointer_cast<ArrayOpenBracket>(m_tokens[start]),
            whiteSpaces
        );
    }
    return std::make_shared<OpenArray>(
            std::dynamic_pointer_cast<ArrayOpenBracket>(m_tokens[start]));

}

std::shared_ptr<OpenObject> TokenHandlers::buildOpenObject(
        std::vector<std::shared_ptr<Character>> &m_tokens, 
        size_t &m_index,
        size_t &start,
        std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    std::cout << "Building an Object Open Bracket  primitive \n";
    if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace){
        m_index++;
        while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
        {
            whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
            m_index++;
        }
        return std::make_shared<OpenObject>( 
            std::dynamic_pointer_cast<ObjectOpenBracket>(m_tokens[start]),
            whiteSpaces
        );
    }
    return std::make_shared<OpenObject>(
            std::dynamic_pointer_cast<ObjectOpenBracket>(m_tokens[start]));
}

std::shared_ptr<ExclamationPrimitive> TokenHandlers::buildExclamation(
        std::vector<std::shared_ptr<Character>> &m_tokens, 
        size_t &m_index,
        size_t &start)
{
    std::cout << "Building a close object primitive \n";
    m_index++;
    
    return std::make_shared<ExclamationPrimitive>
    (
        std::dynamic_pointer_cast<Exclamation>(m_tokens[start])
    );
}

std::shared_ptr<EqualPrimitive> TokenHandlers::buildEqual(
        std::vector<std::shared_ptr<Character>> &m_tokens, 
        size_t &m_index,
        size_t &start)
{
    std::cout << "Building an equal primitive \n";
    m_index++;
    
    return std::make_shared<EqualPrimitive>
    (
        std::dynamic_pointer_cast<EqualSymbol>(m_tokens[start])
    );
}