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
    std::cout << "First token " << tokens.at(10)->getValue() << "\n"; 
    CharacterReader reader = CharacterReader(tokens);  
    reader.displayCharacterTokens();
}

void CharacterReader::displayCharacterTokens(){
    std::cout << "Total tokens" << this->m_tokens.size() << "\n";
    for(auto token : this->m_tokens)
    {
        std::cout << token->getType() << " - " << token->getValue() << "\n";
    }
}

/** 
 * Function that takes the reader of tokens and
 *  then analyzes and assigns types to them
 */
// Value* read_form(std::optional<std::string_view> token) 
// {   
//     if(!token) return nullptr; 
    
//     //read the first char of a token
//     switch (token.value()[0]) 
//     {
//         case '<': //its a tag of some sort
//         {
//             auto tag =  readTag(token);
//             return tag; 
//         }    

//         default: //its a child string of some sort
//         {
//             auto stringValue =  readStringValue(token);
//             return stringValue; 
//         }    
//     }
// }

/** 
 *  Creates StringValues from the tokens determined 
 *   to be strings by the reader
 */
// Value* readStringValue(std::optional<std::string_view> &token) 
// {
//     return new StringValue(*token); 
// }

//analyzes the tag tokens Starts with "<" and assigns the correct tag
// Value* readTag(std::optional<std::string_view> &token)
// {
//     size_t m_index { 0 }; // position in string
//     //check the second characters
//     if(token.value().length() > 1)
//     {   
//         m_index++; 
//         switch(token.value()[m_index])
//         {
//             case '!':  // could be a comment or doc tag
//             {
//                 m_index++; 
//                 char c = token.value()[m_index]; 
//                 switch(c)
//                 {
//                     case '-': // comment
//                     {
//                         return new CommentValue(*token); 
//                     } 
//                     default: //anything else is a doc tag
//                         return new DocumentTagValue(*token); 
//                 }
//             };
//             case '?': //xml start tag
//             {
//                 return new XmlTagValue(*token); 
//             }
//             case '/': //xml closing tag
//             {
//                 return new EndTagValue(*token); 
//             }
//             default: //opening tag or self_closing tag
//             {
//                 while(m_index < token.value().length()){
//                     m_index++; 
//                 char c = token.value()[m_index]; 
//                     if(c == '/')
//                     {
//                         return new SelfClosingTagValue(*token);     
//                     }
//                 }
//                 return new StartTagValue(*token); 

//             }
//         }   
//     }
//     return nullptr; 
// }
