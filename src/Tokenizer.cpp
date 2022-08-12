#include "Tokenizer.hpp"

//creates a vector tokens
void Tokenizer::tokenize() 
{
    
    
    while (auto token = this->next()) 
    {
        this->tokens.push_back(token);
    }
}

/**
 * @brief Function to read string character by character
 * to retrieve character tokens
 * 
 * @return Character object
 */
std::shared_ptr<Character>Tokenizer::next()
{
    auto view = std::string_view(m_input);
    while (this->m_index < this->m_input.length()) 
    {
        char c = this->m_input.at(this->m_index); 
        int start = this->m_index; 
        switch(c)
        {
            case ' ':
            case '\t':
            case '\n':
            case '\r':
                std::cout << "white space found." << "\n";
                m_index++; 
                return 
                std::make_shared<WhiteSpace>(std::string(view.substr(start, 1)));
            case '@':
            case '#':
            case '$':
            case '%':
            case '^':
            case '&':
            case '*':
            case '(':
            case ')':
            case '+':
            case '`':
            case '~':
            case '.':
            case ';': 
            case '|':
                m_index++; 
                std::cout << "Symbol space found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Symbol>(std::string(view.substr(start, 1)));
            case '!':
                m_index++; 
                std::cout << "Exclamation found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Exclamation>(std::string(view.substr(start, 1)));
            case '\'':
                m_index++; 
                std::cout << "Single Quote found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<SingleQuote>(std::string(view.substr(start, 1)));
            case '"':
                m_index++; 
                std::cout << "Double Quote found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Quote>(std::string(view.substr(start, 1)));
            case '\\':
                switch(m_input.at(m_index+1))
                {
                    case '\'':
                        std::cout << "Escaped Single Quote found. " << std::string(view.substr(start, 2)) <<   "\n";
                        m_index++;
                        m_index++; 
                        return std::make_shared<EscapedSingleQuote>(std::string(view.substr(start, 2)));
                    case '\"':
                        std::cout << "Escaped Quote found. " << std::string(view.substr(start, 2)) <<   "\n";
                        m_index++;
                        m_index++; 
                        return std::make_shared<EscapedQuote>(std::string(view.substr(start, 2)));
                    default:
                        std::cout << "Symbol found. " << std::string(view.substr(start, 1)) <<   "\n";
                        m_index++; 
                        return std::make_shared<Symbol>(std::string(view.substr(start, 1)));
                }
            case '{':
                m_index++; 
                std::cout << "Object Bracket Open found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<ObjectOpenBracket>(std::string(view.substr(start, 1))));
            case '}':
                m_index++; 
                std::cout << "Object Bracket Close found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<ObjectCloseBracket>(std::string(view.substr(start, 1))));
            case '[':
                m_index++; 
                std::cout << "Array Bracket Open found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<ArrayOpenBracket>(std::string(view.substr(start, 1))));
            case ']':
                m_index++; 
                std::cout << "Array Bracket Close found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<ArrayCloseBracket>(std::string(view.substr(start, 1))));
            case ':':
                m_index++; 
                std::cout << "Colon found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<Colon>(std::string(view.substr(start, 1))));
            case '?':
                m_index++; 
                std::cout << "Question mark found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<QuestionMark>(std::string(view.substr(start, 1))));
            case '>':
                m_index++; 
                std::cout << "Close bracket found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<CloseBracket>(std::string(view.substr(start, 1))));
            case '<':
                m_index++; 
                std::cout << "Open bracket found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<OpenBracket>(std::string(view.substr(start, 1))));
            case '-':
                m_index++; 
                std::cout << "Dash found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<Dash>(std::string(view.substr(start, 1))));
            case '/':
                m_index++; 
                std::cout << "Forward Slash found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::dynamic_pointer_cast<Character>(std::make_shared<ForwardSlash>(std::string(view.substr(start, 1))));
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                m_index++; 
                std::cout << "Lowercase letter found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Lowercase>(std::string(view.substr(start, 1)));
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                m_index++; 
                std::cout << "Uppercase letter found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Uppercase>(std::string(view.substr(start, 1)));
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                m_index++; 
                std::cout << "Number found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<Number>(std::string(view.substr(start, 1)));
            }
            default:
                m_index++; 
                std::cout << "Unicode found. " << std::string(view.substr(start, 1)) <<   "\n";
                return std::make_shared<UnicodeCharacter>(std::string(view.substr(start, 1)));
        };
    }
    return {};
}