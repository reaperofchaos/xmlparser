#include "TokenHandlers.hpp"

std::shared_ptr<NumberType> TokenHandlers::buildNumberComponent(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<Number>> &numbers)
{
    
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

    if(whiteSpaces.size() > 0){
        return std::make_shared<CloseObject>(whiteSpaces,
            std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[m_index]));
    }
    m_index++;
    return std::make_shared<CloseObject>(std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[m_index-1]));
    
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

    m_index++;
    while(m_tokens[m_index]->type() != CharacterType::WhiteSpace &&
    (m_tokens[m_index]->symbolType() != SymbolType::CloseBracket) &&
    (m_tokens[m_index]->symbolType() != SymbolType::EqualSymbol) &&
    (m_tokens[m_index]->symbolType() != SymbolType::Colon) &&
    (m_tokens[m_index]->symbolType() != SymbolType::Comma) &&
    (m_tokens[m_index]->symbolType() != SymbolType::Semicolon))
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

    m_index++; 
    if(symbolType == SymbolType::SingleQuote)
    {
        while( m_tokens[m_index]->symbolType() != SymbolType::SingleQuote)
            {
                characters.push_back(m_tokens[m_index]);
                m_index++;
            }
        m_index++;
        return std::make_shared<StringType>( 
            std::dynamic_pointer_cast<SingleQuote>(m_tokens[start]),
            characters,
            std::dynamic_pointer_cast<SingleQuote>(m_tokens[m_index-1])
        );
    }else{
        while( m_tokens[m_index]->symbolType() != SymbolType::Quote)
        {
            characters.push_back(m_tokens[m_index]);
            m_index++;
        }
        m_index++;
        return std::make_shared<StringType>( 
            std::dynamic_pointer_cast<Quote>(m_tokens[start]),
            characters,
            std::dynamic_pointer_cast<Quote>(m_tokens[m_index-1])
        );
    }
}

std::shared_ptr<OpenArray> TokenHandlers::buildOpenArray(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{

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

std::shared_ptr<ExclamationComponent> TokenHandlers::buildExclamation(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start)
{

    m_index++;
    
    return std::make_shared<ExclamationComponent>
    (
        std::dynamic_pointer_cast<Exclamation>(m_tokens[start])
    );
}

std::shared_ptr<EqualComponent> TokenHandlers::buildEqual(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<EqualComponent>
    (
        std::dynamic_pointer_cast<EqualSymbol>(m_tokens[m_index -1])
    );
}

std::shared_ptr<SemicolonComponent> TokenHandlers::buildSemicolon(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<SemicolonComponent>
    (
        std::dynamic_pointer_cast<Semicolon>(m_tokens[m_index -1])
    );
}

std::shared_ptr<ColonComponent> TokenHandlers::buildColon(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<ColonComponent>
    (
        std::dynamic_pointer_cast<Colon>(m_tokens[m_index -1])
    );
}

std::shared_ptr<PercentageComponent> TokenHandlers::buildPercentage(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<PercentageComponent>
    (
        std::dynamic_pointer_cast<Percentage>(m_tokens[m_index -1])
    );
}

std::shared_ptr<CommaComponent> TokenHandlers::buildComma(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<CommaComponent>
    (
        std::dynamic_pointer_cast<Comma>(m_tokens[m_index -1])
    );
}

std::shared_ptr<HashTagComponent> TokenHandlers::buildHashTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index)
{
    m_index++;
    
    return std::make_shared<HashTagComponent>
    (
        std::dynamic_pointer_cast<HashTag>(m_tokens[m_index -1])
    );
}

std::shared_ptr<StringType> TokenHandlers::buildNestedString(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<Character>> &characters)
{
    characters.push_back(m_tokens[m_index]);
    m_index++;

    while(
        m_tokens[m_index]->symbolType() != SymbolType::OpenBracket &&
        m_tokens[m_index]->symbolType() != SymbolType::ObjectOpenBracket &&
        m_tokens[m_index]->symbolType() != SymbolType::Dash )
    {
        characters.push_back(m_tokens[m_index]);
        m_index++;
    }

    return std::make_shared<StringType>(characters);
}


std::shared_ptr<ClosingOpenTag> TokenHandlers::buildClosingOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start)
{
    m_index++; //forward slash
    m_index++; 
    return std::make_shared<ClosingOpenTag>
    (
        std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
        std::dynamic_pointer_cast<ForwardSlash>(m_tokens[m_index-1])
    );
}

std::shared_ptr<CommentOpenTag> TokenHandlers::buildCommentOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{

    m_index++; //first dash
    m_index++; //second dash
    m_index++; //next token
    return std::make_shared<CommentOpenTag>
    (
        std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
        whiteSpaces,
        std::dynamic_pointer_cast<Exclamation>(m_tokens[m_index -3]),
        std::dynamic_pointer_cast<Dash>(m_tokens[m_index -2]),
        std::dynamic_pointer_cast<Dash>(m_tokens[m_index -1])
    );
}

std::shared_ptr<CommentCloseTag> TokenHandlers::buildCommentCloseTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{

    m_index++;
    m_index++;
    TokenHandlers::findWhiteSpace(m_tokens, m_index, whiteSpaces); 
    m_index++;
    return std::make_shared<CommentCloseTag>
    (
        std::dynamic_pointer_cast<Dash>(m_tokens[start]),
        std::dynamic_pointer_cast<Dash>(m_tokens[start+1]),
        whiteSpaces,
        std::dynamic_pointer_cast<CloseBracket>(m_tokens[m_index-1])
    );
}

std::shared_ptr<DocumentTypeOpenTag> TokenHandlers::buildDocumentTypeOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{

    m_index++; //next token
    return std::make_shared<DocumentTypeOpenTag>
    (
        std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
        whiteSpaces,
        std::dynamic_pointer_cast<Exclamation>(m_tokens[m_index-1])
    );
}

void TokenHandlers::findWhiteSpace(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{
    if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace){
        m_index++;
        while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
        {
            whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
            m_index++;
        }
    }
}

std::shared_ptr<OpenTag> TokenHandlers::buildOpenTag(
    std::vector<std::shared_ptr<Character>> &m_tokens, 
    size_t &m_index,
    size_t &start,
    std::vector<std::shared_ptr<WhiteSpace>> &whiteSpaces)
{   
    m_index++; 
    return std::make_shared<OpenTag>
    (
        std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
        whiteSpaces
    );

}