#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <optional>
#include "Types.hpp"

/**
 * @brief Class to break down string into smaller chunks
 * which are either tags, strings or untracked 
 * new line or return characters
 * 
 */
class Tokenizer{
    private:
        std::string &m_input; // string input
        size_t m_index { 0 }; // position in string
    
    public: 
        Tokenizer(std::string &input)
            : m_input{input}{};
        
        /**
         * @brief Function to read string character by character
         * to retrieve tags (which could be metatags, comments, start or end tags)
         * 
         * @return std::optional<std::string_view> 
         */
        std::optional<std::string_view> next()
        {
            auto view = std::string_view(m_input);
            while (m_index < m_input.length()) 
            {
                char c = m_input.at(m_index); 
                switch(c)
                {
                    case ' ':
                    case '\t':
                    case '\n':
                    case '\r':
                        ++m_index; 
                        break; 
                    case '<': //found a tag start
                    {
                        size_t start = m_index;
                        ++m_index;
                        while(m_index < m_input.length())
                        {
                            c = m_input.at(m_index); 
                            switch(c)
                            {
                                case '>': //END OF A TAG
                                    ++m_index;
                                    std::cout << "Found tag " << view.substr(start, m_index - start) << "\n"; 
                                    return view.substr(start, m_index - start);
                                default:
                                    ++m_index; 
                            }
                        }
                        if(m_index == m_input.length() )
                        {
                            std::cout << "EOF\n";
                        }
                        return view.substr(start, m_index - start); 

                    }
                    default: //should just be child values at this point
                    {    
                        size_t start = m_index;
                        bool done = false; 
                        while (!done && m_index < m_input.length()){
                            c = m_input.at(m_index); 
                            switch(c)
                            {
                                case '<': //end at the start of a new tag
                                case '>': // or something stupid like a mismatched closing tag
                                    done = true; 
                                    break;
                                default: 
                                    ++m_index;
                                    break; 
                            }
                        }
                        if(m_index == m_input.length() )
                        {
                            std::cout << "EOF\n";
                        }
                        return view.substr(start, m_index - start);
                    }
                }
            }
            return {};
        }

        // parse tags, probably should be in a reader


        // std::optional<std::string_view> handleTag(){
        //     size_t start = m_index;
        //     m_index++; 
        //     char c = m_input.at(m_index); 
        //     auto view = std::string_view(m_input);

        //     switch(c){
        //         case '!': {
        //             //Doc Type tag
        //             if(m_input.at(m_index + 1) != '-'){
        //             while(c != '>'){
        //                 m_index++; 
        //             }
        //             return view.substr(start, m_index - start);
        //             }else{ // comment tag
                         
        //                 /* parse the comment */
        //                 m_index++; //consume the -'s
        //                 while(m_input.at(m_index)== '-'){
        //                     m_index++; //consume the -
        //                 }
        //                 size_t commentStart = m_index; 
        //                 size_t commentEnd = 0; 
        //                 while(c != '>'){
        //                     if(c == '-'){
        //                         if(m_input.at(m_index +1) == '-')
        //                         {
        //                             commentEnd = m_index -1; 
        //                         }
        //                     }
        //                     m_index++; 
        //                 }
        //                 return view.substr(commentStart, commentEnd - commentStart);
        //             }
        //         }
        //         case '?':{
        //             //xml start tag <?xml >
        //              while(c != '>'){
        //                 m_index++; 
        //             }
        //             return view.substr(start, m_index - start);
        //         }
        //         case '/':{
        //             //closing tag
        //             while (c != '>'){
        //                 m_index++; 
        //             }
        //              return view.substr(start, m_index - start);

        //         }
                
        //         default: {
        //             //start tag or self-closing tag
        //             while (c != '>'){
        //                 //self closing tag <tag />
        //                 if(c == '/'  && m_input.at(m_index + 1) != '>'){
        //                     m_index++;
        //                     return view.substr(start, m_index - start);
        //                 }
        //                 m_index++; 
        //             }
        //             //start tag <tag>
        //             return view.substr(start, m_index - start);
        //         }                
        //     }
        // }
};