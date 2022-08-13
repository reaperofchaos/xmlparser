#include "CharacterReader.hpp"

/** 
 * function to read a string, 
 * tokenizes and analyzes the tokens 
 * and returns an Abstract Syntax Tree
 **/
void CharacterReader::read_str(std::string input) 
{
    Tokenizer tokenizer = Tokenizer(input);
    tokenizer.tokenize();
    std::vector<std::shared_ptr<Character>>tokens = tokenizer.getTokens(); 
    std::cout << "Total tokens " << tokens.size() << "\n"; 
    CharacterReader reader = CharacterReader(tokens);  
    reader.displayCharacterTokens();   
    reader.build_primitives();
    std::vector<std::shared_ptr<Primitive>>primitives = reader.getPrimitives(); 
    std::cout << "Total primitives " << primitives.size() << "\n"; 
    reader.displayPrimitives();
}

std::shared_ptr<Primitive>CharacterReader::next(){
    size_t start = this->m_index;
    std::vector<std::shared_ptr<Character>> characters;
    std::vector< std::shared_ptr<Number>> numbers;
    std::vector<std::shared_ptr<WhiteSpace>> whiteSpaces;

    //handle strings between tags
    if(
        m_index > 0 &&
        m_index < m_tokens.size() &&
        m_tokens[m_index -1]->symbolType() == SymbolType::CloseBracket &&
        m_tokens[m_index]->type() != CharacterType::Symbol) 
        return TokenHandlers::buildNestedString(m_tokens, m_index, characters);

    while (this->m_index < this->m_tokens.size())
    {
        std::cout << m_tokens[m_index]->inspect() << "\n";
        switch(m_tokens[m_index]->type())
        {
            case CharacterType::Number: //Build a number
                return TokenHandlers::buildNumberPrimitive(m_tokens, m_index, numbers);

            case CharacterType::WhiteSpace:
                whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
                m_index++;
                
                while(m_tokens[m_index]->type() == CharacterType::WhiteSpace && this->m_index < this->m_tokens.size())
                {
                    whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
                    m_index++;
                }
                if(this->m_index < this->m_tokens.size())
                {
                    switch(m_tokens[m_index]->type())
                    {
                        case CharacterType::Symbol:
                            switch(m_tokens[m_index]->symbolType())
                            {
                                case SymbolType::CloseBracket:
                                    return TokenHandlers::buildCloseTag(m_tokens, m_index, whiteSpaces);
                                case SymbolType::ArrayCloseBracket:
                                    return TokenHandlers::buildCloseArray(m_tokens, m_index, whiteSpaces);
                                case SymbolType::ObjectCloseBracket:
                                    return TokenHandlers::buildCloseObject(m_tokens, m_index, whiteSpaces);
                                default:
                                    return TokenHandlers::buildWhiteSpaces(whiteSpaces);
                            }
                        default:
                            return TokenHandlers::buildWhiteSpaces(whiteSpaces);
                    }
                }
                return TokenHandlers::buildWhiteSpaces(whiteSpaces);

            case CharacterType::Letter:
            case CharacterType::Uppercase:
            case CharacterType::Lowercase:
                return TokenHandlers::buildName(m_tokens, m_index, start, characters);

            case CharacterType::Symbol:
                switch(m_tokens[m_index]->symbolType())
                {
                    case SymbolType::ForwardSlash:
                        TokenHandlers::buildClosingCloseTag(m_tokens, m_index, start);
                    
                    case SymbolType::OpenBracket: // build the start of a tag
                        std::cout << "Building an open tag primitive \n";
                        std::cout << m_tokens[m_index+1]->inspect() << "\n"; 
                        if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace){
                            m_index++;
                            while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
                            {
                                whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
                                m_index++;
                            }
                            if(m_tokens[m_index+1]->type() == CharacterType::Symbol && m_tokens[m_index+1]->symbolType() == SymbolType::ForwardSlash)
                            {
                                m_index++; 
                                return std::make_shared<ClosingOpenTag>
                                (
                                    std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
                                    std::dynamic_pointer_cast<ForwardSlash>(m_tokens[m_index-1])
                                );
                            }
                            return std::make_shared<OpenTag>
                            (
                                std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
                                whiteSpaces
                            );
                        }
                        if(m_tokens[m_index+1]->type() == CharacterType::Symbol && m_tokens[m_index+1]->symbolType() == SymbolType::ForwardSlash)
                        {
                            m_index++; 
                            m_index++; 
                            return std::make_shared<ClosingOpenTag>
                            (
                                std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
                                std::dynamic_pointer_cast<ForwardSlash>(m_tokens[m_index-1])
                            ); 
                        }
                        m_index++;
                        return std::make_shared<OpenTag>(
                            std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]));
                    
                    case SymbolType::ArrayOpenBracket: //build the start of an array 
                        return TokenHandlers::buildOpenArray(m_tokens, m_index, start, whiteSpaces);
                    
                    case SymbolType::ObjectOpenBracket: //build the start of an object
                        return TokenHandlers::buildOpenObject(m_tokens, m_index, start, whiteSpaces);

                    case SymbolType::SingleQuote: //build the string
                        return TokenHandlers::buildString(m_tokens, m_index, start, characters, SymbolType::SingleQuote);
                        
                    case SymbolType::Quote: //build the string
                        return TokenHandlers::buildString(m_tokens, m_index, start, characters, SymbolType::Quote);

                    case SymbolType::CloseBracket:
                        return TokenHandlers::buildCloseTag(m_tokens, m_index, whiteSpaces);
                        
                    case SymbolType::ArrayCloseBracket:
                        return TokenHandlers::buildCloseArray(m_tokens, m_index, whiteSpaces);

                    case SymbolType::ObjectCloseBracket:
                        return TokenHandlers::buildCloseObject(m_tokens, m_index, whiteSpaces);

                    case SymbolType::Exclamation:
                        return TokenHandlers::buildExclamation(m_tokens, m_index, start);
                    
                    case SymbolType::EqualSymbol:
                        return TokenHandlers::buildEqual(m_tokens, m_index);

                    default: 
                        m_index++;
                        return {};
                }
            default:
                    m_index++;
                    return {};
        }
    } 
    return {};
}

/**
 * @brief Displays the type and value of the tokens
 * 
 */
void CharacterReader::displayCharacterTokens(){
    for(auto token : this->m_tokens)
    {
        std::cout << token->getType() << " - " << token->getValue() << "\n";
    }
}

/**
 * @brief Builds primitives from the characters
 * 
 */
void CharacterReader::build_primitives() 
{
    while (auto primitive = this->next()) 
    {
        this->m_primitives.push_back(primitive);
    }
}

/**
 * @brief Displays the type and value of the primitives
 * 
 */
void CharacterReader::displayPrimitives()
{
    for(auto primitive : this->m_primitives)
    {
        std::cout << primitive->getType() << " - " << primitive->getValue() << "\n";
    }
}
