#include "Reader.hpp"

//creates a vector tokens
std::vector<std::string_view> tokenize(std::string &input) 
{
    Tokenizer tokenizer { input };
    std::vector<std::string_view> vector;
    while (auto token = tokenizer.next()) 
    {
        vector.push_back(*token);
    }
    return vector;
}

/** 
 * function to read a string, 
 * tokenizes and then analyzes the tokens*/
Value *read_str(std::string &input) 
{
    auto tokens = tokenize(input);
    Reader reader { tokens };
    Value* tag =  read_form(reader);
    return tag; 
}

/** 
 * Function that takes the reader of tokens and
 *  then analyzes and assigns types to them
 */
Value* read_form(Reader &reader) 
{
    auto token = reader.peek();
    if (!token)
        return nullptr;
    //read the first char of a token
    switch (token.value()[0]) 
    {
        case '<': //its a tag of some sort
        {
            auto tag =  readTag(token);
            std::cout <<"found tag " << tag->str() << "\n"; 
            return tag; 
        }    

        default: //its a child string of some sort
        {
            auto stringValue =  readStringValue(token);
            return stringValue; 
        }    
    }
}

/** 
 *  Creates StringValues from the tokens determined 
 *   to be strings by the reader
 */
Value* readStringValue(std::optional<std::string_view> &token) 
{
    return new StringValue(*token); 
}

//analyzes the tag tokens Starts with "<" and assigns the correct tag
Value* readTag(std::optional<std::string_view> &token)
{
    size_t m_index { 0 }; // position in string
    //check the second characters
    if(token.value().length() > 1)
    {   
        m_index++; 
        switch(token.value()[m_index])
        {
            case '!':  // could be a comment or doc tag
            {
                m_index++; 
                char c = token.value()[m_index]; 
                switch(c)
                {
                    case '-': // comment
                    {
                        return new CommentValue(*token); 
                    } 
                    default: //anything else is a doc tag
                        return new DocumentTagValue(*token); 
                }
            };
            case '?': //xml start tag
            {
                return new XmlTagValue(*token); 
            }
            case '/': //xml closing tag
            {
                return new EndTagValue(*token); 
            }
            default: //opening tag or self_closing tag
            {
                while(m_index < token.value().length()){
                    m_index++; 
                char c = token.value()[m_index]; 
                    if(c == '/')
                    {
                        return new SelfClosingTagValue(*token);     
                    }
                }
                return new StartTagValue(*token); 

            }
        }   
    }
    return nullptr; 
}
