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
    
    while (this->m_index < this->m_tokens.size())
    {
        switch(m_tokens[m_index]->type())
        {
            case CharacterType::Number: //Build a number
                std::cout << "Building a number primitive \n";
                while(m_tokens[m_index]->type() == CharacterType::Number)
                {
                    numbers.push_back(std::make_shared<Number>(m_tokens[m_index]->getValue()));
                    m_index++; 
                }
                return std::make_shared<NumberType>(numbers);
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
                                    std::cout << "Building a close bracket primitive \n";
                                    return std::make_shared<CloseTag>(whiteSpaces, 
                                            std::dynamic_pointer_cast<CloseBracket>(m_tokens[m_index]));
                                case SymbolType::ArrayCloseBracket:
                                    std::cout << "Building an array close bracket primitive \n";
                                    return std::make_shared<CloseArray>(whiteSpaces,
                                            std::dynamic_pointer_cast<ArrayCloseBracket>(m_tokens[m_index]));
                                case SymbolType::ObjectCloseBracket:
                                    std::cout << "Building an object close bracket primitive \n";
                                    return std::make_shared<CloseObject>(whiteSpaces,
                                            std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[m_index]));

                                default:
                                    return {};
                            }
                        default:
                            return {};
                    }
                }
                return {};

            case CharacterType::Symbol:
                switch(m_tokens[m_index]->symbolType())
                {
                    case SymbolType::OpenBracket: // build the start of a tag
                        std::cout << "Building an open tag primitive \n";
                        if(m_tokens[m_index+1]->type() == CharacterType::WhiteSpace){
                            m_index++;
                            while(m_tokens[m_index]->type() == CharacterType::WhiteSpace)
                            {
                                whiteSpaces.push_back(std::make_shared<WhiteSpace>(m_tokens[m_index]->getValue()));
                                m_index++;
                            }
                            return std::make_shared<OpenTag>
                            (
                                std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]),
                                whiteSpaces
                            );
                        }
                        m_index++;
                        return std::make_shared<OpenTag>(
                            std::dynamic_pointer_cast<OpenBracket>(m_tokens[start]));
                    case SymbolType::ArrayOpenBracket: //build the start of an array 
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
                    case SymbolType::ObjectOpenBracket: //build the start of an object
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
                    case SymbolType::SingleQuote: //build the string
                        std::cout << "Building a string \n";
                        m_index++; 
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
                    case SymbolType::Quote: //build the string
                        std::cout << "Building a string \n";
                        m_index++; 
                        while(m_tokens[m_index]->symbolType() != SymbolType::Quote)
                        {
                            characters.push_back(m_tokens[m_index]);
                            m_index++;
                        }
                        return std::make_shared<StringType>( 
                            std::dynamic_pointer_cast<Quote>(m_tokens[start]),
                            characters,
                            std::dynamic_pointer_cast<Quote>(m_tokens[m_index])
                        );
                    case SymbolType::CloseBracket:
                        std::cout << "Building a close tag primitive \n";
                        m_index++;
                        return std::make_shared<CloseTag>
                        (
                            std::dynamic_pointer_cast<CloseBracket>(m_tokens[start])
                        );
                    case SymbolType::ArrayCloseBracket:
                        std::cout << "Building a close array primitive \n";
                        m_index++;
                        return std::make_shared<CloseArray>
                        (
                            std::dynamic_pointer_cast<ArrayCloseBracket>(m_tokens[start])
                        );

                    case SymbolType::ObjectCloseBracket:
                        std::cout << "Building a close object primitive \n";
                        m_index++;
                        
                        return std::make_shared<CloseObject>
                        (
                            std::dynamic_pointer_cast<ObjectCloseBracket>(m_tokens[start])
                        );
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


void CharacterReader::displayCharacterTokens(){
    std::cout << "Total tokens" << this->m_tokens.size() << "\n";
    for(auto token : this->m_tokens)
    {
        std::cout << token->getType() << " - " << token->getValue() << "\n";
    }
}

void CharacterReader::build_primitives() 
{
    while (auto primitive = this->next()) 
    {
        this->m_primitives.push_back(primitive);
    }
}
void CharacterReader::displayPrimitives()
{
    for(auto primitive : this->m_primitives)
    {
        std::cout << primitive->getType() << " - " << primitive->getValue() << "\n";
    }
}